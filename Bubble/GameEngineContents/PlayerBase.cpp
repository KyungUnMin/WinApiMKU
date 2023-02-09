#include "PlayerBase.h"
#include <queue>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsDefine.h"
#include "PlayerFSM.h"
#include "Gravity.h"
#include "BubbleSpawner.h"
#include "BubbleMissle.h"
#include "BubbleMissleFSM.h"

const float4 PlayerBase::CollisionOffset = float4{0.f, -30.f};
const float4 PlayerBase::CollisionScale = float4{ 50.f, 50.f };

PlayerBase::PlayerBase()
{
	FsmPtr = new PlayerFSM;
}

//�÷��̾ ��� �ִ� ������Ʈ���� delete
PlayerBase::~PlayerBase()
{
	if (nullptr != FsmPtr)
	{
		delete FsmPtr;
		FsmPtr = nullptr;
	}


	for (auto Pair : Components)
	{
		if (nullptr != Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	}

	Components.clear();
}



PlayerCharacterType PlayerBase::GetCharacterType()
{
	if (CharcterType == PlayerCharacterType::COUNT)
	{
		MsgAssert("�÷��̾� Ÿ���� ���������� �ʾҽ��ϴ�");
		return PlayerCharacterType::COUNT;
	}

	return CharcterType;
}

void PlayerBase::Start()
{
	CollisionPtr = CreateCollision(CollisionOrder::Player);
	CollisionPtr->SetScale(CollisionScale);
	CollisionPtr->SetPosition(CollisionOffset);

	FsmPtr->Player = this;
	FsmPtr->Start();

	BBSpawner = GetLevel()->CreateActor<BubbleSpawner>();
	BBSpawner->SetPlayer(this);

	//�÷��̾ ����� ������Ʈ ����
	//Components[ComponentType::PlayerState] = new PlayerFSM;
	Components[ComponentType::Gravity] = new Gravity;


	//�÷��̾��� ������Ʈ�� �ʱ�ȭ
	for (auto Pair : Components)
	{
		//������Ʈ�� �����ڴ� this
		Pair.second->SetOwner(this);
		Pair.second->Start();
	}
}

/*
���� ������ ���� ���� ����
���߿� FSM���� ������ ������ �� �ְԲ� �� ����
�ƴϸ� FSM�ȿ� ������ �����ϰ� �־ �� ���ϴ�
*/


void PlayerBase::Update(float _DeltaTime)
{
	//�� ��ü�� ������ üũ
	MovableActor::CheckDirection();

	FsmPtr->Update(_DeltaTime);

	//������Ʈ�� Update�� �۵�
	for (auto Pair : Components)
	{
		Pair.second->Update(_DeltaTime);
	}

	//�÷��̾�� ������ �浹 ó���� ���� ���������� �Ͷ߸���
	BubbleCollisionCheck();
}

void PlayerBase::BubbleCollisionCheck()
{
	//�� �÷��̾ ����� �浹�ߴٸ� �浹�� ������� ��������
	std::vector<GameEngineCollision*> BubbleCollision;
	if (false == CollisionPtr->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player_Missle) }, BubbleCollision))
		return;

	//�÷��̾�� �浹�� ������ ť�� ��´�
	std::queue<BubbleMissle*> BubbleQ;
	for (GameEngineCollision* BubbleCol : BubbleCollision)
	{
		BubbleMissle* Bubble = dynamic_cast<BubbleMissle*>(BubbleCol->GetActor());
		if (nullptr == Bubble)
		{
			MsgAssert("UpdateOrder::Player_Missle�� BubbleMissle�� �ƴ� ��ü�� �����մϴ�");
			return;
		}

		//�÷��̾�� �浹�� ������ popó��
		Bubble->GetFSM()->ChangeState(BubbleStateType::Pop);

		//������ ����Pop�� ���� ť�� ��´�
		BubbleQ.push(Bubble);
	}

	//���� ������ �����ϴ� ������� ��� ������
	auto Bubbles = GetLevel()->GetActors(static_cast<int>(UpdateOrder::Player_Missle));
	while (BubbleQ.size())
	{
		BubbleMissle* NowBubble = BubbleQ.front();
		BubbleQ.pop();

		for (GameEngineActor* BubbleActor : Bubbles)
		{
			BubbleMissle* NextBubble = dynamic_cast<BubbleMissle*>(BubbleActor);
			if (nullptr == NextBubble)
			{
				MsgAssert("UpdateOrder::Player_Missle�� BubbleMissle�� �ƴ� ��ü�� �����մϴ�");
				return;
			}

			//Idle������ ����� Move������ ���� �����Ͷ߸��� ó��
			BubbleMissleFSM* NextFSM = NextBubble->GetFSM();
			if (BubbleStateType::Idle != NextFSM->GetCurStateType()
				&& BubbleStateType::Move != NextFSM->GetCurStateType())
			{
				continue;
			}

			//��� ť���� Pop�� ������ ��ġ, ���� Ȯ���� ������ ��ġ, �������� ����
			float4 NowPos = NowBubble->GetPos();
			float4 NextPos = NextBubble->GetPos();
			float4 BubbleColScale = BubbleMissle::CollisionScale * 1.5f;

			//�浹 �� ��ü�鸸
			if (false == GameEngineCollision::CollisionCircleToCircle({ NowPos, BubbleColScale }, { NextPos, BubbleColScale }))
				continue;

			NextFSM->ChangeState(BubbleStateType::Pop);
			BubbleQ.push(NextBubble);
		}
	}

}
