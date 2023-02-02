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

//플레이어가 들고 있던 컴포넌트들을 delete
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
		MsgAssert("플레이어 타입을 설정해주지 않았습니다");
		return PlayerCharacterType::COUNT;
	}

	return CharcterType;
}

void PlayerBase::Start()
{
	CollisionPtr = CreateCollision(CollisionOrder::Player);
	CollisionPtr->SetScale(CollisionScale);
	CollisionPtr->SetPosition(CollisionOffset);

	//플레이어가 사용할 컴포넌트 생성
	Components[ComponentType::PlayerState] = new PlayerState;
	Components[ComponentType::Gravity] = new Gravity;
	Components[ComponentType::BubbleSpawner] = new BubbleSpawner;


	//플레이어의 컴포넌트를 초기화
	for (auto Pair : Components)
	{
		//컴포넌트의 소유자는 this
		Pair.second->SetOwner(this);
		Pair.second->Start();
	}
}


void PlayerBase::Update(float _DeltaTime)
{
	//이 객체의 방향을 체크
	MovableActor::CheckDirection();

	//컴포넌트의 Update를 작동
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
			MsgAssert("버블이 아닌 객체가 버블 충돌 그룹에 속해있습니다");
			return;
		}

		if (BubbleState::Idle != Bubble->GetState())
			continue;

		Bubble->BubblePop();
	}
}
