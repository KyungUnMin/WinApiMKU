#include "MonsterState_RocketDash.h"
#include "MonsterFSM.h"
#include "PlayerBase.h"


MonsterState_RocketDash::MonsterState_RocketDash()
{

}

MonsterState_RocketDash::~MonsterState_RocketDash()
{

}

void MonsterState_RocketDash::Start()
{
	MonsterStateBase::Start();
	SetNowAniName("RocketDash");
}

void MonsterState_RocketDash::Update(float _DeltaTime)
{
	//몬스터 객체에서 지정해준 우선 처리 사항
	StateChangeFuncPtr IsChangeState = GetStateChangeFunc();
	if (nullptr != IsChangeState)
	{
		if (true == (GetMonster()->*IsChangeState)(_DeltaTime))
			return;
	}

	//움직임을 처리하고 벽에 막혔다면
	if (false == GetMonster()->MoveHorizon(DashSpeed.x, MonsterBase::CollisionScale, _DeltaTime))
	{
		//만약 공중에 있어도 Falling이 될 것
		GetFSM()->ChangeState(MonsterStateType::Move);
		return;
	}

	//플레이어와 충돌했을때
	if (true == PlayerCollisionCheck())
	{
		PlayerBase::MainPlayer->AttackPlayer();
		return;
	}
}
