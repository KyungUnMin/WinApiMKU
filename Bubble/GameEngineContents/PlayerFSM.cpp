#include "PlayerFSM.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "PlayerBase.h"
#include "PlayerState_Idle.h"
#include "PlayerState_Move.h"
#include "PlayerState_Falling.h"
#include "PlayerState_Jump.h"
#include "PlayerState_StageMove.h"
#include "PlayerState_Sleep.h"
#include "PlayerState_Damaged.h"
#include "PlayerState_Enter.h"
#include "PlayerState_Embarrassed.h"

PlayerFSM::PlayerFSM()
{

}

//가지고 있던 컴포넌트들을 delete
PlayerFSM::~PlayerFSM()
{
	for (size_t i = 0; i < States.size(); ++i)
	{
		if (nullptr != States[i])
		{
			delete States[i];
		}
	}
}








void PlayerFSM::Start()
{
	if (nullptr == Player)
	{
		MsgAssert("PlayerFSM을 초기화해주기 전에 FSM의 Player를 설정해주어야 합니다");
		return;
	}

	States.resize(static_cast<size_t>(PlayerStateType::Count), nullptr);
	for (size_t i = 0; i < States.size(); ++i)
	{
		//생성
		CreateState(static_cast<PlayerStateType>(i));

		//이 FSM을 관리하고 있는 클래스로 자기자신을 등록
		States[i]->SetFSM(this);
		//이 FSM이 가르키고 있는 객체 등록(Player의 FSM이기 때문에 플레이어 등록)
		States[i]->SetPlayer(Player);

		//플레이어 타입에 따라 FSM 초기화
		States[i]->Start(Player->GetCharacterType());
	}

	//처음 FSM은 Idle로 설정
	CurState = GetState(PlayerStateType::Idle);
	CurState->EnterState();
}





//타입에 따라 컴포넌트 생성
void PlayerFSM::CreateState(PlayerStateType _StateType)
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
	case PlayerStateType::EnterDoor:
		States[Index] = new PlayerState_Enter;
		break;
	case PlayerStateType::Embarrassed:
		States[Index] = new PlayerState_Embarrassed;
		break;
	default:
		MsgAssert("해당 State를 아직 PlayerState와 연결시켜 주지 않았습니다");
		break;
	}
}





//현재 플레이어의 State를 Enum으로 반환
PlayerStateType PlayerFSM::GetCurStateByEnum()
{
	for (size_t i = 0; i < States.size(); ++i)
	{
		if (CurState != States[i])
			continue;

		return static_cast<PlayerStateType>(i);
	}

	MsgAssert("아직 연결해주지 않은 State입니다");
	return PlayerStateType::Count;
}


//enum으로 받은 값을 States에서 찾아 반환
PlayerStateBase* PlayerFSM::GetState(PlayerStateType _Type)
{
	if (PlayerStateType::Count == _Type)
	{
		MsgAssert("Count는 유효하지 않은 접근입니다");
		return nullptr;
	}

	return States[static_cast<size_t>(_Type)];
}

//FSM 변경
void PlayerFSM::ChangeState(PlayerStateBase* _NextState)
{
	PlayerStateBase* NextState = _NextState;
	PlayerStateBase* PrevState = CurState;

	//FSM변경
	CurState = _NextState;

	//이전 FSM이 다른 FSM으로 바뀔때 처리
	PrevState->ExitState();

	//전환되는 FSM으로 들어올때
	NextState->EnterState();
}

GameEngineRender* PlayerFSM::GetRender()
{
	return Player->GetRender();
}




//현재 FSM 동작
void PlayerFSM::Update(float _DeltaTime)
{
	if (nullptr == CurState)
	{
		MsgAssert("현재 상태를 지정해주지 않았습니다");
		return;
	}

	CurState->Update(_DeltaTime);
}



#include "BubbleCore.h"
void PlayerFSM::DebugRender()
{
	if (false == BubbleCore::GetInst().IsDebug())
		return;

	std::string DebugStr = "현재 플레이어의 상태 : ";
	PlayerStateType CurStateEnum = GetCurStateByEnum();

	switch (CurStateEnum)
	{
	case PlayerStateType::Idle:
		DebugStr += "Idle";
		break;
	case PlayerStateType::Move:
		DebugStr += "Move";
		break;
	case PlayerStateType::Falling:
		DebugStr += "Falling";
		break;
	case PlayerStateType::Jump:
		DebugStr += "Jump";
		break;
	case PlayerStateType::StageMove:
		DebugStr += "StageMove";
		break;
	case PlayerStateType::Sleep:
		DebugStr += "Sleep";
		break;
	case PlayerStateType::Damaged:
		DebugStr += "Damaged";
		break;
	case PlayerStateType::EnterDoor:
		DebugStr += "EnterDoor";
		break;
	default:
		DebugStr += "UNKNOWN";
		break;
	}

	GameEngineLevel::DebugTextPush(DebugStr);
}
