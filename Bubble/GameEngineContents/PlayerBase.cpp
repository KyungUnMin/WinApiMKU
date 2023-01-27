#include "PlayerBase.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "ContentsDefine.h"
#include "PlayerState.h"
#include "Gravity.h"

PlayerBase::PlayerBase()
{
	
}

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



void PlayerBase::Start()
{
	static bool IsCreatedKey = false;
	if (false == IsCreatedKey)
	{
		IsCreatedKey = true;

		GameEngineInput::CreateKey(PlayerLeft, LeftKey);
		GameEngineInput::CreateKey(PlayerRight, RightKey);
		GameEngineInput::CreateKey(PlayerJump, JumpKey);
		GameEngineInput::CreateKey(PlayerAttack, AttackKey);
	}

	Components[ComponentType::PlayerState] = new PlayerState;
	Components[ComponentType::Gravity] = new Gravity;

	for (auto Pair : Components)
	{
		Pair.second->SetOwner(this);
		Pair.second->Start();
	}
}


void PlayerBase::Update(float _DeltaTime)
{
	MovableActor::Update(_DeltaTime);

	for (auto Pair : Components)
	{
		Pair.second->Update(_DeltaTime);
	}
}
