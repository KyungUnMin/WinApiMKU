#include "BossState_Dead.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>
#include "BossMonster.h"
#include "BossMonsterFSM.h"
#include "BossDeadEffect.h"
#include "BossDeadPoint.h"
#include "RoundLevelBase.h"

BossState_Dead::BossState_Dead()
{

}

BossState_Dead::~BossState_Dead()
{

}


void BossState_Dead::Start()
{
	LoadSFX();
	RoundLevel = dynamic_cast<RoundLevelBase*>(GetBoss()->GetLevel());
}

void BossState_Dead::EnterState()
{
	BossMonster* Boss = GetBoss();
	GameEngineRender* RenderPtr = Boss->GetRender();
	RenderPtr->ChangeAnimation(BossMonster::DeadAniName);

	SelectDirection();
	GameEngineResources::GetInst().SoundPlay("BossDead.mp3");

	BossDeadPoint* RewardPoint = Boss->GetLevel()->CreateActor<BossDeadPoint>(UpdateOrder::PointEffect);
	RewardPoint->SetPos(Boss->GetPos());

	Boss->DestroyHpBar();

	RoundLevel->StageBossClear();
}

void BossState_Dead::LoadSFX()
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
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("BossDead.mp3"));
	IsLoad = true;
}

void BossState_Dead::SelectDirection()
{
	ScreenSize = GameEngineWindow::GetScreenSize();

	NowSpeed = StartSpeed;
	float4 ThisPos = GetBoss()->GetPos();

	if (ScreenSize.hx() < ThisPos.x)
	{
		NowSpeed.x = -StartSpeed.x;
	}
}




void BossState_Dead::Update(float _DeltaTime)
{
	CreateEffect(_DeltaTime);
	Move(_DeltaTime);
}

void BossState_Dead::Move(float _DeltaTime)
{
	NowSpeed.y += (Gravity * _DeltaTime);
	GetBoss()->SetMove(NowSpeed * _DeltaTime);

	float4 ThisPos = GetBoss()->GetPos();
	if ((ScreenSize.y + ScreenOutOffset.y) < ThisPos.y)
	{
		GetBoss()->Death();
	}
}

void BossState_Dead::CreateEffect(float _DeltaTime)
{
	static float Timer = 0.f;
	const float CreateTime = 0.25f;
	const float MaxRadius = 200.f;

	Timer += _DeltaTime;
	if (Timer < CreateTime)
		return;

	GetBoss()->GetLevel()->CreateActor<BossDeadEffect>(UpdateOrder::PointEffect);
	Timer -= CreateTime;
}
