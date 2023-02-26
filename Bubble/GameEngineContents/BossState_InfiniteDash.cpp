#include "BossState_InfiniteDash.h"
#include "BossMonster.h"


BossState_InfiniteDash::BossState_InfiniteDash()
{

}

BossState_InfiniteDash::~BossState_InfiniteDash()
{

}


void BossState_InfiniteDash::EnterState()
{
	ChangeAniDir(BossMonster::RageAngryAniName);
	CalcDirection();
}

void BossState_InfiniteDash::Move(float _DeltaTime)
{
	const float	MoveSpeed = 400.f;
	float4 NowPos = GetBoss()->GetPos();
	float4 NextPos = NowPos + (GetDir() * MoveSpeed * _DeltaTime);
	float4 CheckPos = NextPos + (GetDir() * BossMonster::CollisionScale.half());

	if (true == IsScreenOutPos(CheckPos))
	{
		CalcDirection();
		ChangeAniDir(BossMonster::RageAngryAniName);
		return;
	}

	GetBoss()->SetPos(NextPos);
}