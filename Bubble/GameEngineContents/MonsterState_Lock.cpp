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

void MonsterState_Lock::Update(float _DeltaTime)
{
	if (nullptr == LockTarget)
		return;

	if (true == PlayerCollisionCheck())
	{
		LockTarget = nullptr;
		//GetFSM()->ChangeState(MonsterStateType::Dead);
		return;
	}

	GetMonster()->SetPos(LockTarget->GetPos());
}

void MonsterState_Lock::EnterState()
{
	GameEngineRender* RenderPtr = GetMonster()->GetRender();
	RenderPtr->ChangeAnimation(GetNowAniName());
	//GetMonster()->GetCollision()->Off();
}

void MonsterState_Lock::ExitState()
{
	//GetMonster()->GetCollision()->On();
}

void MonsterState_Lock::Locked(BubbleMissle* _LockedBubble)
{
	LockTarget = _LockedBubble;
}