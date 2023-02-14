#include "MonsterState_Lock.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include "BubbleMissle.h"
#include "PlayerBase.h"
#include "BubbleMissle.h"
#include "MonsterFSM.h"

MonsterState_Lock::MonsterState_Lock()
{

}

MonsterState_Lock::~MonsterState_Lock()
{

}

void MonsterState_Lock::Start()
{
	SetNowAniName("Lock");
}



void MonsterState_Lock::EnterState()
{
	GameEngineRender* RenderPtr = GetMonster()->GetRender();
	RenderPtr->ChangeAnimation(GetNowAniName());
}