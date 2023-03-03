#include "MonsterState_Dead.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "RigidBody.h"
#include "PlayerBase.h"
#include "MonsterFSM.h"
#include "MonsterBase.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include "Item_Normal.h"
#include "PointPannel.h"

MonsterState_Dead::MonsterState_Dead()
{
}

MonsterState_Dead::~MonsterState_Dead()
{
	
}

void MonsterState_Dead::Start()
{
	LoadSFX();
	SetNowAniName("Dead");
	ScreenSize = GameEngineWindow::GetScreenSize();

	SetSpeed();
}



void MonsterState_Dead::EnterState()
{
	GameEngineRender* RenderPtr = GetMonster()->GetRender();
	RenderPtr->ChangeAnimation(GetNowAniName());

	SetSpeed();
	if (nullptr != PlayerBase::MainPlayer)
	{
		NowSpeed.x *= PlayerBase::MainPlayer->GetDirVec().x;
	}

	PointPannel::AddPoint(KillPoint);
	GameEngineResources::GetInst().SoundPlay("MonsterDead.wav");
	Timer = 0.f;
}

void MonsterState_Dead::SetSpeed()
{
	const float4 HighSpeed = float4{ 1200.f, -1000.f };
	const float4 LowSpeed = float4{ 200.f, -400.f };

	NowSpeed.x = GameEngineRandom::MainRandom.RandomFloat(LowSpeed.x, HighSpeed.x);
	NowSpeed.y = GameEngineRandom::MainRandom.RandomFloat(HighSpeed.y, LowSpeed.y);
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

	//만약에 특이한 경우로 땅에 닿지 않는 경우를 대비해 시간에 따라 처리
	Timer += _DeltaTime;
	if (DeathTime < Timer)
	{
		GetFSM()->ChangeState(MonsterStateType::Falling);
		return;
	}

	//Dead처리
	if ((0.f < NowSpeed.y) && (ScreenSize.hy() < NextPos.y) && true == GetMonster()->IsGround({ 2.f, 2.f }))
	{
		GetFSM()->ChangeState(MonsterStateType::Falling);
		return;
	}

	//화면 아래로 나갔을때 처리
	if (ScreenSize.y < NextPos.y)
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

void MonsterState_Dead::LoadSFX()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");
	Dir.Move("SFX");
	Dir.Move("Monster");

	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("MonsterDead.wav"));
	IsLoad = true;
}
