#include "BossState_CircleMove.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include "BubbleCore.h"
#include "BossMonster.h"

BossState_CircleMove::BossState_CircleMove()
{
	DebugPen = static_cast<HPEN>(CreatePen(PS_SOLID, 5, RGB(0, 0, 255)));
}

BossState_CircleMove::~BossState_CircleMove()
{
	DeleteObject(DebugPen);
}

void BossState_CircleMove::Start()
{
	const float4 Offset = float4{ 0.f, -150.f };
	Pivot = GameEngineWindow::GetScreenSize().half() + Offset;
	ChangeAniDir(BossMonster::IdleAniName);
}

void BossState_CircleMove::EnterState()
{
	ChangeAniDir(BossMonster::IdleAniName);
}

void BossState_CircleMove::Update(float _DeltaTime)
{
	static float PrevDist = FLT_MAX;

	float4 BossPos = GetBoss()->GetPos();
	float4 DirToPivot = Pivot - BossPos;
	float Distance = DirToPivot.Size();

	//회전 반경 안에 있을때
	if (Distance < Radius)
	{
		//이번 프레임에 원 안으로 들어왔다면
		if ((Radius < PrevDist) && (Distance < Radius))
		{
			//중심점에서 보스 몬스터 까지의 벡터의 각도를 구한다
			RotateAngle = (-DirToPivot).GetAngleDeg();
			PrevDist = 0.f;
			return;
		}

		//회전이동
		Update_CircleMove(_DeltaTime, Distance);
	}

	//회전 반경 밖에 있을때
	else
	{
		//중심 위치로 이동
		Update_MoveToPivot(_DeltaTime, DirToPivot);
		PrevDist = Distance;
	}


}

void BossState_CircleMove::Update_CircleMove(float _DeltaTime, float _Distance)
{
	const float RotateSpeed = 90.f;
	RotateAngle += RotateSpeed * _DeltaTime;
	if (360.f < RotateAngle)
	{
		RotateAngle -= 360.f;
	}

	float4 DEBUG = GetBoss()->GetPos();

	float4 Dir = float4::AngleToDirection2DToDeg(RotateAngle);
	Dir.y *= -1.f;
	float4 NextPos = Pivot + (Dir * _Distance);
	GetBoss()->SetPos(NextPos);
}



void BossState_CircleMove::Update_MoveToPivot(float _DeltaTime, float4 _Dir)
{
	const float MoveSpeed = 150.f;

	_Dir.Normalize();
	GetBoss()->SetMove(_Dir * MoveSpeed * _DeltaTime);
}










void BossState_CircleMove::Render(float _DeltaTime)
{
	if (false == BubbleCore::GetInst().IsDebug())
		return;

	HDC DoubleBufferDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	DebugPen = static_cast<HPEN>(SelectObject(DoubleBufferDC, DebugPen));

	Ellipse(DoubleBufferDC,
		static_cast<int>(Pivot.x - Radius),
		static_cast<int>(Pivot.y - Radius),
		static_cast<int>(Pivot.x + Radius),
		static_cast<int>(Pivot.y + Radius));

	DebugPen = static_cast<HPEN>(SelectObject(DoubleBufferDC, DebugPen));
}