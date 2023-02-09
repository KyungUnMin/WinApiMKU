#include "BubbleMissleFSM.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "BubbleMissle.h"
#include "BubbleMissleStateBase.h"

#include "BubbleStateThrow.h"
#include "BubbleStateMove.h"
#include "BubbleStateIdle.h"
#include "BubbleStatePop.h"

BubbleMissleFSM::BubbleMissleFSM()
{

}

BubbleMissleFSM::~BubbleMissleFSM()
{
	for (size_t i = 0; i < static_cast<size_t>(BubbleStateType::Count); ++i)
	{
		if (nullptr != States[i])
		{
			delete States[i];
			States[i] = nullptr;
		}
	}

	States.clear();
}

void BubbleMissleFSM::Start(PlayerCharacterType _CharType, BubbleMissleType _BubbleType)
{
	States.resize(static_cast<size_t>(BubbleStateType::Count), nullptr);

	for (size_t i = 0; i < States.size(); ++i)
	{
		//����
		CreateState(static_cast<BubbleStateType>(i));

		//�� FSM�� �����ϰ� �ִ� Ŭ������ �ڱ��ڽ��� ���
		States[i]->Fsm = this;

		//Bubble ��ü�� �� Ŭ������ �����Ǿ����� Bubble���� ����
		States[i]->Bubble = this->Bubble;

		//FSM State �ʱ�ȭ
		States[i]->Init(_CharType, _BubbleType);
	}

	//ó�� FSM�� Idle�� ����
	CurState = GetState(BubbleStateType::Throw);
	CurState->EnterState();
}



void BubbleMissleFSM::CreateState(BubbleStateType _StateType)
{
	size_t Index = static_cast<size_t>(_StateType);

	switch (_StateType)
	{
	case BubbleStateType::Throw:
		States[Index] = new BubbleStateThrow;
		break;
	case BubbleStateType::Move:
		States[Index] = new BubbleStateMove;
		break;
	case BubbleStateType::Idle:
		States[Index] = new BubbleStateIdle;
		break;
	case BubbleStateType::Pop:
		States[Index] = new BubbleStatePop;
		break;
	//case BubbleStateType::Imminent:
	//	//States[Index] = new 
	//	break;

	default:
		MsgAssert("�ش� State�� ���� PlayerState�� ������� ���� �ʾҽ��ϴ�");
		break;
	}
}


BubbleMissleStateBase* BubbleMissleFSM::GetState(BubbleStateType _Type)
{
	if (BubbleStateType::Count == _Type)
	{
		MsgAssert("Count�� ��ȿ���� ���� �����Դϴ�");
		return nullptr;
	}

	return States[static_cast<size_t>(_Type)];
}


//FSM ����
void BubbleMissleFSM::ChangeState(BubbleStateType _NextStateType)
{
	//���� FSM�� �ٸ� FSM���� �ٲ� ó��
	CurState->ExitState();

	//��ȯ�Ǵ� FSM���� ���ö�
	BubbleMissleStateBase* NextState = GetState(_NextStateType);
	NextState->EnterState();

	//FSM����
	CurState = NextState;
	CurType = _NextStateType;
}


void BubbleMissleFSM::Update(float _DeltaTime)
{
	if (nullptr == CurState)
	{
		MsgAssert("���� ���¸� ���������� �ʾҽ��ϴ�");
		return;
	}

	CurState->Update(_DeltaTime);
}
