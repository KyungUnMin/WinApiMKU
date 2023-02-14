#include "MonsterState_Dead.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "RigidBody.h"
#include "PlayerBase.h"

MonsterState_Dead::MonsterState_Dead()
{
}

MonsterState_Dead::~MonsterState_Dead()
{
	
}

void MonsterState_Dead::Start()
{
	SetNowAniName("Dead");
	ScreenSize = GameEngineWindow::GetScreenSize();
}

void MonsterState_Dead::EnterState()
{
	GameEngineRender* RenderPtr = GetMonster()->GetRender();
	RenderPtr->ChangeAnimation(GetNowAniName());

	
	NowSpeed.x *= PlayerBase::MainPlayer->GetDirVec().x;
}

void MonsterState_Dead::Update(float _DeltaTime)
{
	NowSpeed += (GravityAcc * _DeltaTime);

	float4 NowPos = GetMonster()->GetPos();
	float4 NextPos = NowPos + (NowSpeed * _DeltaTime);

	//ÃµÀå¿¡ ºÎµúÈù °æ¿ì
	if (NextPos.y < 0)
	{
		NowSpeed.y = 0.f;
		return;
	}

	//È­¸é ÁÂ¿ì¿¡ ºÎµúÈù °æ¿ì
	if (NextPos.x < 0.f || ScreenSize.x < NextPos.x)
	{
		NowSpeed.x *= -1.f;
		return;
	}

	if ((ScreenSize.y - DeathVertical) < NextPos.y)
	{
		GetMonster()->Death();
		return;
	}

	GetMonster()->SetPos(NextPos);
}


