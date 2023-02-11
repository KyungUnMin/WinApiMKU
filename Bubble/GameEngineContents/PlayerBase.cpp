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
	FSMPtr = new PlayerFSM;
}

//�÷��̾ ��� �ִ� ������Ʈ���� delete
PlayerBase::~PlayerBase()
{
	if (nullptr != FSMPtr)
	{
		delete FSMPtr;
		FSMPtr = nullptr;
	}
}









void PlayerBase::Start()
{
	MovableActor::Start();

	CollisionPtr = CreateCollision(CollisionOrder::Player);
	CollisionPtr->SetScale(CollisionScale);
	CollisionPtr->SetPosition(CollisionOffset);


	FSMPtr->Player = this;
	FSMPtr->Start();


	BBSpawner = GetLevel()->CreateActor<BubbleSpawner>();
	BBSpawner->SetPlayer(this);
}



void PlayerBase::Update(float _DeltaTime)
{
	//�� ��ü�� ������ üũ
	MovableActor::Update(_DeltaTime);

	FSMPtr->Update(_DeltaTime);

	/*if (GameEngineInput::IsDown(PLAYER_ATTACK))
	{
		FsmPtr->PlayerAttack();
		BBSpawner->CreateBubble(GetDirVec());
	}*/

	//BubbleCollisionCheck();
}

void PlayerBase::Render(float _DeltaTime)
{
	MovableActor::Render(_DeltaTime);
	FSMPtr->DebugRender();	
}







//�÷��̾�� ������ �浹 ó���� ���� ���������� �Ͷ߸���
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







PlayerCharacterType PlayerBase::GetCharacterType()
{
	if (CharcterType == PlayerCharacterType::COUNT)
	{
		MsgAssert("�÷��̾� Ÿ���� ���������� �ʾҽ��ϴ�");
		return PlayerCharacterType::COUNT;
	}

	return CharcterType;
}

