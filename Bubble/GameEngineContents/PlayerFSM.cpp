#include "PlayerFSM.h"
#include <GameEngineBase/GameEngineDebug.h>

#include "PlayerBase.h"
#include "PlayerState_Idle.h"
#include "PlayerState_Move.h"
#include "PlayerState_Falling.h"
#include "PlayerState_Jump.h"
#include "PlayerState_StageMove.h"
#include "PlayerState_Sleep.h"
#include "PlayerState_Damaged.h"
#include "PlayerState_Enter.h"

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

	default:
		MsgAssert("�ش� State�� ���� PlayerState�� ������� ���� �ʾҽ��ϴ�");
		break;
	}
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
	//���� FSM�� �ٸ� FSM���� �ٲ� ó��
	CurState->ExitState();

	//��ȯ�Ǵ� FSM���� ���ö�
	_NextState->EnterState();

	//FSM����
	CurState = _NextState;
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