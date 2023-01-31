#include "PlayerState.h"
#include <GameEngineBase/GameEngineDebug.h>

#include "PlayerBase.h"
#include "PlayerState_Idle.h"
#include "PlayerState_Move.h"
#include "PlayerState_Falling.h"
#include "PlayerState_Jump.h"
#include "PlayerState_StageMove.h"
#include "PlayerState_Sleep.h"
#include "PlayerState_Damaged.h"

PlayerState::PlayerState()
{

}

//가지고 있던 컴포넌트들을 delete
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


//(PlayerBase를 상속받은 객체에서 직접 호출)
//자료구조에 모든 FSM들을 생성하고 관리
void PlayerState::Init(PlayerCharacterType _CharacterType)
{
	States.resize(static_cast<size_t>(PlayerStateType::Count), nullptr);
	PlayerBase* Player = dynamic_cast<PlayerBase*>(GetOwner());

	for (size_t i = 0; i < States.size(); ++i)
	{
		//생성
		CreateState(static_cast<PlayerStateType>(i));

		//이 FSM을 관리하고 있는 클래스로 자기자신을 등록
		States[i]->SetOwner(this);
		//이 FSM이 가르키고 있는 객체 등록(Player의 FSM이기 때문에 플레이어 등록)
		States[i]->SetPlayer(Player);

		//플레이어 타입에 따라 FSM 초기화
		States[i]->Start(_CharacterType);
	}

	//처음 FSM은 Idle로 설정
	CurState = GetState(PlayerStateType::Idle);
	CurState->EnterState();
}


//타입에 따라 컴포넌트 생성
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
	case PlayerStateType::StageMove:
		States[Index] = new PlayerState_StageMove;
		break;
	case PlayerStateType::Sleep:
		States[Index] = new PlayerState_Sleep;
		break;
	case PlayerStateType::Damaged:
		States[Index] = new PlayerState_Damaged;
		break;

	default:
		MsgAssert("해당 State를 아직 PlayerState와 연결시켜 주지 않았습니다");
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


//FSM 변경
void PlayerState::ChangeState(PlayerStateBase* _NextState)
{
	//이전 FSM이 다른 FSM으로 바뀔때 처리
	CurState->ExitState();

	//전환되는 FSM으로 들어올때
	_NextState->EnterState();

	//FSM변경
	CurState = _NextState;
}

//현재 FSM 동작
void PlayerState::Update(float _DeltaTime)
{
	if (nullptr == CurState)
	{
		MsgAssert("Player초기화를 해주지 않았습니다(PlayerBase::Init)");
		return;
	}

	CurState->Update(_DeltaTime);
}