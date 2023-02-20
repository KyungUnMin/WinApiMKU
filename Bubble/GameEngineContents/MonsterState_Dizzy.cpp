#include "MonsterState_Dizzy.h"
#include "MonsterFSM.h"

const std::string_view MonsterState_Dizzy::AniName = "Dizzy";

MonsterState_Dizzy::MonsterState_Dizzy()
{

}

MonsterState_Dizzy::~MonsterState_Dizzy()
{

}


void MonsterState_Dizzy::Start()
{
	SetNowAniName(AniName);
}

void MonsterState_Dizzy::EnterState()
{
	MonsterStateBase::EnterState();
	AccTime = 0.f;
	NowDirChangeCnt = 0;
}

void MonsterState_Dizzy::Update(float _DeltaTime)
{
	AccTime += _DeltaTime;

	if(RaiseChangeTime <  AccTime)
	{
		GetFSM()->ChangeState(MonsterStateType::RaiseFly);
		return;
	}

	float DirTime = RaiseChangeTime / DirChangeCnt;
	if ((DirTime * NowDirChangeCnt) < AccTime)
	{
		GetMonster()->SetReverseDir();
		ChangeAniDir();
		++NowDirChangeCnt;
	}
	
}

