#include "PlayerState.h"
#include <GameEngineBase/GameEngineDebug.h>

#include "PlayerBase.h"
#include "PlayerState_Idle.h"
#include "PlayerState_Move.h"


PlayerState::PlayerState()
{

}

PlayerState::~PlayerState()
{
	for (size_t i = 0; i < States.size(); ++i)
	{
		if (nullptr != States[i])
		{
			delete States[i];
		}
	}
}



void PlayerState::Init(PlayerCharacterType _CharacterType)
{
	States.resize(static_cast<size_t>(PlayerStateType::Count), nullptr);

	for (size_t i = 0; i < States.size(); ++i)
	{
		CreateState(static_cast<PlayerStateType>(i));
		States[i]->Owner = this;
		States[i]->Player = dynamic_cast<PlayerBase*>(GetOwner());
		States[i]->Init(_CharacterType);
	}

	CurState = GetState(PlayerStateType::Idle);
	CurState->EnterState();
}


void PlayerState::CreateState(PlayerStateType _StateType)
{
	size_t Index = static_cast<size_t>(_StateType);

	switch (_StateType)
	{
	case PlayerStateType::Idle:
		States[Index] = new PlayerState_Idle;
		break;
	case PlayerStateType::Move:
		States[Index] = new PlayerState_Move;
		break;
	}
}


PlayerStateBase* PlayerState::GetState(PlayerStateType _Type)
{
	if (PlayerStateType::Count == _Type)
	{
		MsgAssert("Count는 유효하지 않은 접근입니다");
		return nullptr;
	}

	return States[static_cast<size_t>(_Type)];
}



void PlayerState::ChangeState(PlayerStateBase* _NextState)
{
	CurState->ExitState();
	_NextState->EnterState();

	CurState = _NextState;
}


void PlayerState::Update(float _DeltaTime)
{
	if (nullptr == CurState)
	{
		MsgAssert("Player초기화를 해주지 않았습니다(PlayerBase::Init)");
		return;
	}

	CurState->Update(_DeltaTime);
}