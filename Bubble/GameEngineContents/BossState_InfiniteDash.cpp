#include "BossState_InfiniteDash.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include "BossMonster.h"
#include "BossMonsterFSM.h"

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
	Timer = 0.f;
}





void BossState_InfiniteDash::Move(float _DeltaTime)
{
	const float	MoveSpeed = 400.f;
	const float ScreenOutOffsetY = 25.f;
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	float4 NowPos = GetBoss()->GetPos();
	float4 NextPos = NowPos + (GetDir() * MoveSpeed * _DeltaTime);
	float4 DownPos = NextPos + (float4::Down * BossMonster::CollisionScale.half());

	if ((ScreenSize.y - ScreenOutOffsetY) < DownPos.y)
	{
		CalcCenterDir();
		ChangeAniDir(BossMonster::RageAngryAniName);
		return;
	}

	float4 CheckPos = NextPos + (GetDir() * BossMonster::CollisionScale.half());
	if (true == IsScreenOutPos(CheckPos))
	{
		CalcDirection();
		ChangeAniDir(BossMonster::RageAngryAniName);
		return;
	}

	GetBoss()->SetPos(NextPos);
}


void BossState_InfiniteDash::CalcCenterDir()
{
	float4 CenterPos = GameEngineWindow::GetScreenSize().half();
	float4 NowPos = GetBoss()->GetPos();

	float4 Dir = CenterPos - NowPos;
	Dir.Normalize();
	SetDir(Dir);

	if (0.f < Dir.x)
	{
		GetBoss()->SetDir(float4::Right);
	}
	else
	{
		GetBoss()->SetDir(float4::Left);
	}
}


void BossState_InfiniteDash::Update(float _DeltaTime)
{
	Timer += _DeltaTime;

	if (ChangeStateTime < Timer)
	{
		GetFSM()->ChangeState(BossStateType::Damaged);
		return;
	}

	BossState_DashToPlayer::Update(_DeltaTime);
}
