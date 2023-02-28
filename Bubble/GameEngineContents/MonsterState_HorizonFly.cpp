#include "MonsterState_HorizonFly.h"
#include "PlayerBase.h"
#include "MonsterFSM.h"
#include "PlayerBase.h"

const std::string_view MonsterState_HorizonFly::AniName = "HorizonFly";

MonsterState_HorizonFly::MonsterState_HorizonFly()
{

}

MonsterState_HorizonFly::~MonsterState_HorizonFly()
{

}

void MonsterState_HorizonFly::Start()
{
	SetNowAniName("HorizonFly");
}


void MonsterState_HorizonFly::EnterState()
{
	MonsterStateBase::EnterState();

	AccTime = 0.f;
	TiredChangeTime = TiredLowTime + static_cast<float>(rand()) * (TiredHighTime - TiredLowTime) / RAND_MAX;
}



void MonsterState_HorizonFly::Update(float _DeltaTime)
{
	AccTime += _DeltaTime;

	if (TiredChangeTime < AccTime)
	{
		GetFSM()->ChangeState(MonsterStateType::Tired);
		return;
	}
	
	//몬스터 이동, 막혔다면 방향전환
	if (false == GetMonster()->MoveHorizon(MoveSpeed.x, MonsterBase::CollisionScale, _DeltaTime))
	{
		GetMonster()->SetReverseDir();
		ChangeAniDir();
	}

	//플레이어와 충돌했을때
	if (true == PlayerCollisionCheck())
	{
		PlayerBase::MainPlayer->AttackPlayer();
	}
}
