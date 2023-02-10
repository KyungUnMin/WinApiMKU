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
#include "PlayerState_IdleAttack.h"
#include "PlayerState_MoveAttack.h"
#include "PlayerState_FallingAttack.h"
#include "PlayerState_JumpAttack.h"
#include "BubbleCore.h"

PlayerFSM::PlayerFSM()
{

}

//������ �ִ� ������Ʈ���� delete
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
		MsgAssert("PlayerFSM�� �ʱ�ȭ���ֱ� ���� FSM�� Player�� �������־�� �մϴ�");
		return;
	}

	RenderPtr = Player->CreateRender(RenderOrder::Player1);
	RenderPtr->SetScale(PlayerRenderScale);

	States.resize(static_cast<size_t>(PlayerStateType::Count), nullptr);
	for (size_t i = 0; i < States.size(); ++i)
	{
		//����
		CreateState(static_cast<PlayerStateType>(i));

		//�� FSM�� �����ϰ� �ִ� Ŭ������ �ڱ��ڽ��� ���
		States[i]->SetOwner(this);
		//�� FSM�� ����Ű�� �ִ� ��ü ���(Player�� FSM�̱� ������ �÷��̾� ���)
		States[i]->SetPlayer(Player);

		//�÷��̾� Ÿ�Կ� ���� FSM �ʱ�ȭ
		States[i]->Start(Player->GetCharacterType());
	}

	//ó�� FSM�� Idle�� ����
	CurState = GetState(PlayerStateType::Idle);
	CurState->EnterState();
}


//Ÿ�Կ� ���� ������Ʈ ����
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
	case PlayerStateType::IdleAttack:
		States[Index] = new PlayerState_IdleAttack;
		break;
	case PlayerStateType::MoveAttack:
		States[Index] = new PlayerState_MoveAttack;
		break;
	case PlayerStateType::FallingAttack:
		States[Index] = new PlayerState_FallingAttack;
		break;
	case PlayerStateType::JumpAttack:
		States[Index] = new PlayerState_JumpAttack;
		break;
	default:
		MsgAssert("�ش� State�� ���� PlayerState�� ������� ���� �ʾҽ��ϴ�");
		break;
	}
}

PlayerStateType PlayerFSM::GetCurStateByEnum()
{
	for (size_t i = 0; i < States.size(); ++i)
	{
		if (CurState != States[i])
			continue;

		return static_cast<PlayerStateType>(i);
	}

	MsgAssert("���� ���������� ���� State�Դϴ�");
	return PlayerStateType::Count;
}




PlayerStateBase* PlayerFSM::GetState(PlayerStateType _Type)
{
	if (PlayerStateType::Count == _Type)
	{
		MsgAssert("Count�� ��ȿ���� ���� �����Դϴ�");
		return nullptr;
	}

	return States[static_cast<size_t>(_Type)];
}


//FSM ����
void PlayerFSM::ChangeState(PlayerStateBase* _NextState)
{
	PlayerStateBase* NextState = _NextState;
	PlayerStateBase* PrevState = CurState;

	//FSM����
	CurState = _NextState;

	//���� FSM�� �ٸ� FSM���� �ٲ� ó��
	PrevState->ExitState();

	//��ȯ�Ǵ� FSM���� ���ö�
	NextState->EnterState();
}

void PlayerFSM::PlayerAttack()
{
	//Attack �ִϸ��̼����� ��ȯ
	if (States[static_cast<int>(PlayerStateType::Idle)] == CurState)
	{
		ChangeState(GetState(PlayerStateType::IdleAttack));
		return;
	}
	else if (States[static_cast<int>(PlayerStateType::Move)] == CurState)
	{
		ChangeState(GetState(PlayerStateType::MoveAttack));
		return;
	}
	else if (States[static_cast<int>(PlayerStateType::Falling)] == CurState)
	{
		ChangeState(GetState(PlayerStateType::FallingAttack));
		return;
	}
	else if (States[static_cast<int>(PlayerStateType::Jump)] == CurState)
	{
		ChangeState(GetState(PlayerStateType::JumpAttack));
		return;
	}

	//�̹� Attack�ִϸ��̼� �����϶� �ִϸ��̼� �ٽ� ���
	if (States[static_cast<int>(PlayerStateType::IdleAttack)] == CurState)
	{
		CurState->PlayerStateBase::EnterState();
		return;
	}
	else if (States[static_cast<int>(PlayerStateType::MoveAttack)] == CurState)
	{
		CurState->PlayerStateBase::EnterState();
		return;
	}
	else if (States[static_cast<int>(PlayerStateType::FallingAttack)] == CurState)
	{
		CurState->PlayerStateBase::EnterState();
		return;
	}
	else if (States[static_cast<int>(PlayerStateType::JumpAttack)] == CurState)
	{
		CurState->PlayerStateBase::EnterState();
		return;
	}

}


//���� FSM ����
void PlayerFSM::Update(float _DeltaTime)
{
	if (nullptr == CurState)
	{
		MsgAssert("���� ���¸� ���������� �ʾҽ��ϴ�");
		return;
	}

	CurState->Update(_DeltaTime);
}

void PlayerFSM::DebugRender()
{
	if (false == BubbleCore::GetInst().IsDebug())
		return;

	std::string DebugStr = "���� �÷��̾��� ���� : ";
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
	case PlayerStateType::IdleAttack:
		DebugStr += "IdleAttack";
		break;
	case PlayerStateType::MoveAttack:
		DebugStr += "MoveAttack";
		break;
	case PlayerStateType::FallingAttack:
		DebugStr += "FallingAttack";
		break;
	case PlayerStateType::JumpAttack:
		DebugStr += "JumpAttack";
		break;
	default:
		DebugStr += "UNKNOWN";
		break;
	}

	GameEngineLevel::DebugTextPush(DebugStr);
}
