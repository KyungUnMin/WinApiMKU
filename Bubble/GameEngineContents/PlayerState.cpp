#include "PlayerState.h"
#include <GameEngineBase/GameEngineDebug.h>

#include "PlayerBase.h"
#include "PlayerState_Idle.h"
#include "PlayerState_Move.h"
#include "PlayerState_Falling.h"
#include "PlayerState_Jump.h"


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
		States[i]->SetOwner(this);
		States[i]->SetPlayer(dynamic_cast<PlayerBase*>(GetOwner()));
		States[i]->Start(_CharacterType);
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
	case PlayerStateType::Falling:
		States[Index] = new PlayerState_Falling;
		break;
	case PlayerStateType::Jump:
		States[Index] = new PlayerState_Jump;
		break;

	default:
		MsgAssert("�ش� State�� ���� PlayerState�� ������� ���� �ʾҽ��ϴ�");
		break;
	}
}


PlayerStateBase* PlayerState::GetState(PlayerStateType _Type)
{
	if (PlayerStateType::Count == _Type)
	{
		MsgAssert("Count�� ��ȿ���� ���� �����Դϴ�");
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
		MsgAssert("Player�ʱ�ȭ�� ������ �ʾҽ��ϴ�(PlayerBase::Init)");
		return;
	}

	CurState->Update(_DeltaTime);
}