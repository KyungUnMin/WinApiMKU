#include "MonsterFSM.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "MonsterStateBase.h"

MonsterFSM::MonsterFSM()
{

}

MonsterFSM::~MonsterFSM()
{
	for (auto Pair : States)
	{
		delete Pair.second;
		Pair.second = nullptr;
	}

	States.clear();
}

void MonsterFSM::Locked(BubbleMissle* _LockedBubble)
{
	CurState->Locked(_LockedBubble);
}



void MonsterFSM::Start()
{
	for (auto Pair : States)
	{
		Pair.second->SetFSM(this);
		Pair.second->SetMonster(MonsterPtr);
		Pair.second->Start();
	}
}

void MonsterFSM::Update(float _DeltaTime)
{
	if (nullptr == CurState)
	{
		MsgAssert("몬스터의 현재 상태를 지정해주지 않았습니다");
		return;
	}

	CurState->Update(_DeltaTime);
}

void MonsterFSM::Render(float _DeltaTime)
{
	if (nullptr == CurState)
	{
		MsgAssert("몬스터의 현재 상태를 지정해주지 않았습니다");
		return;
	}

	CurState->Render(_DeltaTime);
}


void MonsterFSM::ChangeState(MonsterStateType _NextState)
{
	auto FindIter = States.find(_NextState);
	if (States.end() == FindIter)
	{
		MsgAssert("생성시킨 적이 없는 State입니다");
		return;
	}

	MonsterStateBase* PrevState = CurState;
	MonsterStateBase* NextState = FindIter->second;
	CurState = NextState;


	if (nullptr != PrevState)
	{
		PrevState->ExitState();
	}

	if (nullptr != NextState)
	{
		NextState->EnterState();
	}
}

MonsterStateType MonsterFSM::GetCurStateByEnum()
{
	for (std::pair<MonsterStateType, MonsterStateBase*> Pair : States)
	{
		if (CurState == Pair.second)
			return Pair.first;
	}

	MsgAssert("현재 State가 MonsterFSM 자료구조에 존재하지 않습니다");
	return MonsterStateType::Dead;
}
