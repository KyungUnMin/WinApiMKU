#include "MonsterState_Tired.h"
#include "MonsterFSM.h"
#include "PlayerBase.h"

const std::string_view MonsterState_Tired::AniName = "Tired";

MonsterState_Tired::MonsterState_Tired()
{

}

MonsterState_Tired::~MonsterState_Tired()
{

}

void MonsterState_Tired::Start()
{
	SetNowAniName(AniName);
}

void MonsterState_Tired::EnterState()
{
	MonsterStateBase::EnterState();

	AccTime = 0.f;
	FallChangeTime = FallLowTime + static_cast<float>(rand()) * (FallHighTime - FallLowTime) / RAND_MAX;
}


void MonsterState_Tired::Update(float _DeltaTime)
{
	AccTime += _DeltaTime;

	if (FallChangeTime < AccTime)
	{
		GetFSM()->ChangeState(MonsterStateType::Falling);
		return;
	}

	//플레이어와 충돌했을때
	if (true == PlayerCollisionCheck())
	{
		PlayerBase::MainPlayer->AttackPlayer();
	}
}


