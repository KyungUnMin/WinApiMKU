#include "PlayerBase.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "ContentsDefine.h"
#include "PlayerState.h"
#include "Gravity.h"

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



void PlayerBase::Start()
{
	//딱 한번 플레이어가 사용할 키 생성
	static bool IsCreatedKey = false;
	if (false == IsCreatedKey)
	{
		IsCreatedKey = true;

		GameEngineInput::CreateKey(PlayerLeft, LeftKey);
		GameEngineInput::CreateKey(PlayerRight, RightKey);
		GameEngineInput::CreateKey(PlayerJump, JumpKey);
		GameEngineInput::CreateKey(PlayerAttack, AttackKey);
	}

	//플레이어가 사용할 컴포넌트 생성
	Components[ComponentType::PlayerState] = new PlayerState;
	Components[ComponentType::Gravity] = new Gravity;


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
	MovableActor::Update(_DeltaTime);

	//컴포넌트의 Update를 작동
	for (auto Pair : Components)
	{
		Pair.second->Update(_DeltaTime);
	}
}
