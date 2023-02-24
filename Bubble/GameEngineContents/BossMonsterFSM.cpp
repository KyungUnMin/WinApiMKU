#include "BossMonsterFSM.h"
#include <GameEngineBase/GameEngineDebug.h>

#include "BossState_CircleMove.h"
#include "BossState_Damaged.h"


BossMonsterFSM::BossMonsterFSM(BossMonster* _Boss)
	:BossPtr(_Boss)
{

}

BossMonsterFSM::~BossMonsterFSM()
{
	for (BossStateBase* State : States)
	{
		if (nullptr != State)
		{
			delete State;
			State = nullptr;
		}
	}

	States.clear();
}



void BossMonsterFSM::Start()
{
	States.resize(static_cast<size_t>(BossStateType::Count), nullptr);

	for (size_t i = 0; i < States.size(); ++i)
	{
		CreateState(static_cast<BossStateType>(i));
	}

	CurState = BossStateType::CircleMove;
}

void BossMonsterFSM::CreateState(BossStateType _Type)
{
	BossStateBase* BossState = nullptr;
	switch (_Type)
	{
	case BossStateType::CircleMove:
		BossState = new BossState_CircleMove;
		break;
	case BossStateType::Damaged:
		BossState = new BossState_Damaged;
		break;
	default:
		MsgAssert("아직 지정된 BossState를 만들어 줄 수 없습니다");
		return;
	}

	BossState->SetFSM(this);
	BossState->Start();
	size_t Index = static_cast<size_t>(_Type);
	States[Index] = BossState;
}








void BossMonsterFSM::Update(float _DeltaTime)
{
	if (BossStateType::Count == CurState)
	{
		MsgAssert("보스의 상태를 지정해주지 않았습니다");
		return;
	}

	States[static_cast<size_t>(CurState)]->Update(_DeltaTime);
}

void BossMonsterFSM::Render(float _DeltaTime)
{
	if (BossStateType::Count == CurState)
	{
		MsgAssert("보스의 상태를 지정해주지 않았습니다");
		return;
	}

	States[static_cast<size_t>(CurState)]->Render(_DeltaTime);
}





void BossMonsterFSM::ChangeState(BossStateType _NextType)
{
	BossStateBase* NextState = States[static_cast<int>(_NextType)];
	BossStateBase* PrevState = States[static_cast<int>(CurState)];

	CurState = _NextType;

	PrevState->ExitState();
	NextState->EnterState();
}