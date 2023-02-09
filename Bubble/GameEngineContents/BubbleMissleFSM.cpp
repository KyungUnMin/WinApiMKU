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
		//생성
		CreateState(static_cast<BubbleStateType>(i));

		//이 FSM을 관리하고 있는 클래스로 자기자신을 등록
		States[i]->Fsm = this;

		//Bubble 객체는 이 클래스가 생성되었을때 Bubble에서 지정
		States[i]->Bubble = this->Bubble;

		//FSM State 초기화
		States[i]->Init(_CharType, _BubbleType);
	}

	//처음 FSM은 Idle로 설정
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
		MsgAssert("해당 State를 아직 PlayerState와 연결시켜 주지 않았습니다");
		break;
	}
}


BubbleMissleStateBase* BubbleMissleFSM::GetState(BubbleStateType _Type)
{
	if (BubbleStateType::Count == _Type)
	{
		MsgAssert("Count는 유효하지 않은 접근입니다");
		return nullptr;
	}

	return States[static_cast<size_t>(_Type)];
}


//FSM 변경
void BubbleMissleFSM::ChangeState(BubbleStateType _NextStateType)
{
	//이전 FSM이 다른 FSM으로 바뀔때 처리
	CurState->ExitState();

	//전환되는 FSM으로 들어올때
	BubbleMissleStateBase* NextState = GetState(_NextStateType);
	NextState->EnterState();

	//FSM변경
	CurState = NextState;
	CurType = _NextStateType;
}


void BubbleMissleFSM::Update(float _DeltaTime)
{
	if (nullptr == CurState)
	{
		MsgAssert("현재 상태를 지정해주지 않았습니다");
		return;
	}

	CurState->Update(_DeltaTime);
}
