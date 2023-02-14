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
		MsgAssert("������ ���� ���¸� ���������� �ʾҽ��ϴ�");
		return;
	}

	CurState->Update(_DeltaTime);
}

void MonsterFSM::Render(float _DeltaTime)
{
	if (nullptr == CurState)
	{
		MsgAssert("������ ���� ���¸� ���������� �ʾҽ��ϴ�");
		return;
	}

	CurState->Render(_DeltaTime);
}


void MonsterFSM::ChangeState(MonsterStateType _NextState)
{
	auto FindIter = States.find(_NextState);
	if (States.end() == FindIter)
	{
		MsgAssert("������Ų ���� ���� State�Դϴ�");
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

	MsgAssert("���� State�� MonsterFSM �ڷᱸ���� �������� �ʽ��ϴ�");
	return MonsterStateType::Dead;
}
