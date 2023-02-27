#include "BossState_Dead.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>
#include "BossMonster.h"
#include "BossMonsterFSM.h"
#include "BossDeadEffect.h"
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

//PopEffect = GetBoss()->CreateRender(RenderOrder::)
	//Pop 이펙트는 별도의 오브젝트로 만들자 거기엔 Point & 버블Pop이펙트도 있을예정
void BossState_Dead::EnterState()
{
	BossMonster* Boss = GetBoss();
	GameEngineRender* RenderPtr = Boss->GetRender();
	RenderPtr->ChangeAnimation(BossMonster::DeadAniName);

	SelectDirection();

	BossDeadEffect* DeadEffect = Boss->GetLevel()->CreateActor<BossDeadEffect>(UpdateOrder::PointEffect);
	DeadEffect->SetPos(Boss->GetPos());
	GameEngineResources::GetInst().SoundPlay("BossDead.mp3");

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
	NowSpeed.y += (Gravity * _DeltaTime);
	GetBoss()->SetMove(NowSpeed * _DeltaTime);

	float4 ThisPos = GetBoss()->GetPos();
	if ((ScreenSize.y + ScreenOutOffset.y) < ThisPos.y)
	{
		GetBoss()->Death();
	}
}

