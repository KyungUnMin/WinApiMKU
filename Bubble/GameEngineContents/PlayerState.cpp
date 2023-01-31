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

//������ �ִ� ������Ʈ���� delete
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


//(PlayerBase�� ��ӹ��� ��ü���� ���� ȣ��)
//�ڷᱸ���� ��� FSM���� �����ϰ� ����
void PlayerState::Init(PlayerCharacterType _CharacterType)
{
	States.resize(static_cast<size_t>(PlayerStateType::Count), nullptr);
	PlayerBase* Player = dynamic_cast<PlayerBase*>(GetOwner());

	for (size_t i = 0; i < States.size(); ++i)
	{
		//����
		CreateState(static_cast<PlayerStateType>(i));

		//�� FSM�� �����ϰ� �ִ� Ŭ������ �ڱ��ڽ��� ���
		States[i]->SetOwner(this);
		//�� FSM�� ����Ű�� �ִ� ��ü ���(Player�� FSM�̱� ������ �÷��̾� ���)
		States[i]->SetPlayer(Player);

		//�÷��̾� Ÿ�Կ� ���� FSM �ʱ�ȭ
		States[i]->Start(_CharacterType);
	}

	//ó�� FSM�� Idle�� ����
	CurState = GetState(PlayerStateType::Idle);
	CurState->EnterState();
}


//Ÿ�Կ� ���� ������Ʈ ����
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


//FSM ����
void PlayerState::ChangeState(PlayerStateBase* _NextState)
{
	//���� FSM�� �ٸ� FSM���� �ٲ� ó��
	CurState->ExitState();

	//��ȯ�Ǵ� FSM���� ���ö�
	_NextState->EnterState();

	//FSM����
	CurState = _NextState;
}

//���� FSM ����
void PlayerState::Update(float _DeltaTime)
{
	if (nullptr == CurState)
	{
		MsgAssert("Player�ʱ�ȭ�� ������ �ʾҽ��ϴ�(PlayerBase::Init)");
		return;
	}

	CurState->Update(_DeltaTime);
}