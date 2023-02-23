#include "MonsterState_Dead.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "RigidBody.h"
#include "PlayerBase.h"
#include "MonsterFSM.h"
#include "MonsterBase.h"
#include "Item_Normal.h"

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

	NowSpeed = OriginSpeed;
	if (nullptr != PlayerBase::MainPlayer)
	{
		NowSpeed.x *= PlayerBase::MainPlayer->GetDirVec().x;
	}
}





void MonsterState_Dead::Update(float _DeltaTime)
{
	NowSpeed += (GravityAcc * _DeltaTime);

	float4 NowPos = GetMonster()->GetPos();
	float4 NextPos = NowPos + (NowSpeed * _DeltaTime);

	//천장에 부딪힌 경우
	if (NextPos.y < 0)
	{
		NowSpeed.y = 0.f;
		GetMonster()->SetPos({ NowPos.x, 0.f });
		return;
	}

	//화면 좌우에 부딪힌 경우
	if (NextPos.x < AreaOffset.x || (ScreenSize.x - AreaOffset.x) < NextPos.x)
	{
		NowSpeed.x *= -1.f;
		return;
	}

	if ((ScreenSize.y - AreaOffset.y) < NextPos.y)
	{
		GetFSM()->ChangeState(MonsterStateType::Falling);
		return;
	}

	GetMonster()->SetPos(NextPos);
}

void MonsterState_Dead::ExitState()
{
	CreateItem();
	GetMonster()->Off();
}

void MonsterState_Dead::CreateItem()
{
	MonsterBase* Monster = GetMonster();
	Item_Normal* Item = Monster->GetLevel()->CreateActor<Item_Normal>(UpdateOrder::Item);
	Item->Init(Monster->GetPos());
}