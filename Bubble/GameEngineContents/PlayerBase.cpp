#include "PlayerBase.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsDefine.h"
#include "PlayerState.h"
#include "Gravity.h"
#include "BubbleSpawner.h"
#include "BubbleMissleBase.h"

const float4 PlayerBase::CollisionScale = float4{ 50.f, 50.f };
const float4 PlayerBase::CollisionOffset = float4{0.f, -30.f};

PlayerBase::PlayerBase()
{
	
}

//�÷��̾ ��� �ִ� ������Ʈ���� delete
PlayerBase::~PlayerBase()
{
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

	//�÷��̾ ����� ������Ʈ ����
	Components[ComponentType::PlayerState] = new PlayerState;
	Components[ComponentType::Gravity] = new Gravity;
	Components[ComponentType::BubbleSpawner] = new BubbleSpawner;


	//�÷��̾��� ������Ʈ�� �ʱ�ȭ
	for (auto Pair : Components)
	{
		//������Ʈ�� �����ڴ� this
		Pair.second->SetOwner(this);
		Pair.second->Start();
	}
}


void PlayerBase::Update(float _DeltaTime)
{
	//�� ��ü�� ������ üũ
	MovableActor::CheckDirection();

	//������Ʈ�� Update�� �۵�
	for (auto Pair : Components)
	{
		Pair.second->Update(_DeltaTime);
	}

	std::vector<GameEngineCollision*> Bubbles;
	if (false == CollisionPtr->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player_Missle) }, Bubbles))
		return;

	for (size_t i = 0; i < Bubbles.size(); ++i)
	{
		BubbleMissleBase* Bubble = dynamic_cast<BubbleMissleBase*>(Bubbles[i]->GetActor());
		if (nullptr == Bubble)
		{
			MsgAssert("������ �ƴ� ��ü�� ���� �浹 �׷쿡 �����ֽ��ϴ�");
			return;
		}

		if (BubbleState::Idle != Bubble->GetState())
			continue;

		Bubble->BubblePop();
	}
}
