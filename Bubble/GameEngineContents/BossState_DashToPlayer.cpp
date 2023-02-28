#include "BossState_DashToPlayer.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include "BossMonster.h"
#include "PlayerBase.h"
#include "BossMonsterFSM.h"
#include "BubbleCore.h"
#include "BossHpBar.h"

BossState_DashToPlayer::BossState_DashToPlayer()
{
	DebugPen = static_cast<HPEN>(CreatePen(PS_SOLID, 5, RGB(0, 0, 255)));
}

BossState_DashToPlayer::~BossState_DashToPlayer()
{
	DeleteObject(DebugPen);
}

void BossState_DashToPlayer::Start()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	const float4 AreaPosOffset = float4{ 0.f, 20.f };
	const float4 AreaScaleOffset = float4{ 100.f, 100.f };

	MoveArea.Position = ScreenSize.half() + AreaPosOffset;
	MoveArea.Scale = ScreenSize - AreaScaleOffset;
}

void BossState_DashToPlayer::EnterState()
{
	CalcDirection();
	ChangeAniDir(BossMonster::AngryAniName);
}



void BossState_DashToPlayer::CalcDirection()
{
	const float MinDirSize = 200.f;

	BossMonster* Boss = GetBoss();
	float BossLiveTime = Boss->GetAliveTime();

	if (BossLiveTime < (PrevTime + CalcTerm))
	{
		Dir = float4::Up;
		return;
	}
	
	float4 StartPos = Boss->GetPos();
	float4 DestPos = float4::Zero;

	if (nullptr != PlayerBase::MainPlayer)
	{
		DestPos = PlayerBase::MainPlayer->GetPos();
	}

	Dir = (DestPos - StartPos);
	float DirSize = Dir.Size();
	if (DirSize < MinDirSize)
	{
		float4 CenterPos = GameEngineWindow::GetScreenSize().half();
		Dir = (CenterPos - StartPos);
	}

	Dir.Normalize();

	if (0.f < Dir.x)
	{
		Boss->SetDir(float4::Right);
	}
	else
	{
		Boss->SetDir(float4::Left);
	}

	PrevTime = BossLiveTime;
}






void BossState_DashToPlayer::Update(float _DeltaTime)
{
	if (true == CheckDamaged())
		return;

	Move(_DeltaTime);

	//플레이어와 충돌처리
	CheckCollisionWithPlayer();
}




bool BossState_DashToPlayer::CheckDamaged()
{
	int DamageCnt = CheckCollisionWithNatureMissle();
	if (DamageCnt == 0)
		return false;

	//공격을 맞고도 HP가 존재했을때
	if (false == BossHpBar::MainBossHP->ExcuteDamage(DamageCnt))
		return false;

	GetFSM()->ChangeState(BossStateType::Lock);
	return true;
}


void BossState_DashToPlayer::Move(float _DeltaTime)
{
	const float	MoveSpeed = 300.f;
	const float ScreenOutOffsetY = 25.f;

	BossPhase NowPhase = BossHpBar::MainBossHP->GetPhase();
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	float4 NowPos = GetBoss()->GetPos();
	float4 NextPos = NowPos + (Dir * MoveSpeed * _DeltaTime);
	float4 DownPos = NextPos + (float4::Down * BossMonster::CollisionScale.half());


	if ((ScreenSize.y - ScreenOutOffsetY) < DownPos.y)
	{
		if (BossPhase::Normal == NowPhase)
		{
			GetFSM()->ChangeState(BossStateType::CircleMove);
		}
		else
		{
			GetFSM()->ChangeState(BossStateType::Damaged);
		}
		return;
	}

	float4 CheckPos = NextPos + (Dir * BossMonster::CollisionScale.half());

	if (true == IsScreenOutPos(CheckPos))
	{
		if (BossPhase::Normal == NowPhase)
		{
			GetFSM()->ChangeState(BossStateType::CircleMove);
		}
		else
		{
			GetFSM()->ChangeState(BossStateType::Damaged);
		}
		
		return;
	}

	GetBoss()->SetPos(NextPos);
}


bool BossState_DashToPlayer::IsScreenOutPos(const float4 _NextPos)
{
	if (_NextPos.x < MoveArea.Left())
		return true;

	if (MoveArea.Right() < _NextPos.x)
		return true;

	if (_NextPos.y < MoveArea.Top())
		return true;

	if (MoveArea.Bot() < _NextPos.y)
		return true;

	return false;
}

void BossState_DashToPlayer::Render(float _DeltaTime)
{
	if (false == BubbleCore::GetInst().IsDebug())
		return;

	HDC DoubleBufferDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	DebugPen = static_cast<HPEN>(SelectObject(DoubleBufferDC, DebugPen));

	Rectangle(DoubleBufferDC,
		static_cast<int>(MoveArea.Left()),
		static_cast<int>(MoveArea.Top()),
		static_cast<int>(MoveArea.Right()),
		static_cast<int>(MoveArea.Bot()));

	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	float4 NowPos = GetBoss()->GetPos();
	float4 NextPos = NowPos;
	while (false == IsScreenOutPos(NextPos))
	{
		NextPos += Dir;
	}

	DrawDebugArrow(NowPos, NextPos);

	DebugPen = static_cast<HPEN>(SelectObject(DoubleBufferDC, DebugPen));
}
