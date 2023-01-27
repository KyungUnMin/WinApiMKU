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
	CheckDirection();

	for (auto Pair : Components)
	{
		Pair.second->Update(_DeltaTime);
	}
}

void PlayerBase::CheckDirection()
{
	DirChanged = false;

	if (true == GameEngineInput::IsPress("PlayerLeft"))
	{
		DirChanged = (Dir != "Left_");
		Dir = "Left_";
	}
	else if (true == GameEngineInput::IsPress("PlayerRight"))
	{
		DirChanged = (Dir != "Right_");
		Dir = "Right_";
	}
}


const float4& PlayerBase::GetDirVec()
{
	if ("Right_" == Dir)
	{
		return float4::Right;
	}
	else if ("Left_" == Dir)
	{
		return float4::Left;
	}

	MsgAssert("방향은 왼쪽과 오른쪽으로만 존재합니다\n 현재 방향은 잘못되었습니다");
	return float4::Zero;
}