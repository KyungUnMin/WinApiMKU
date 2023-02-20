#include "MonsterState_RaiseFly.h"
#include "MonsterFSM.h"

const std::string_view MonsterState_RaiseFly::AniName = "RaiseFly";

MonsterState_RaiseFly::MonsterState_RaiseFly()
{

}

MonsterState_RaiseFly::~MonsterState_RaiseFly()
{

}

void MonsterState_RaiseFly::Start()
{
	SetNowAniName(AniName);
}

void MonsterState_RaiseFly::EnterState()
{
	MonsterStateBase::EnterState();

	NowBoost = 0;
	MoveTimer = 0.f;
}


void MonsterState_RaiseFly::Update(float _DeltaTime)
{
	if (BoostCnt <= NowBoost)
	{
		GetFSM()->ChangeState(MonsterStateType::HorizonFly);
		return;
	}

	MoveTimer += _DeltaTime;
	float Ratio = MoveTimer / BoostTime;
	float4 NowSpeed = float4::LerpClamp(OriginSpeed, float4::Zero, Ratio);
	GetMonster()->SetMove(float4::Up *  NowSpeed * _DeltaTime);

	if (float4::Zero == NowSpeed)
	{
		++NowBoost;
		MoveTimer -= BoostTime;
	}

}

