#include "BossState_Damaged.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include "BossMonster.h"
#include "BossMonsterFSM.h"
#include "BossHpBar.h"

const std::string_view	BossState_Damaged::SteamImagePath		= "BossAngrySteam.bmp";
const std::string_view	BossState_Damaged::SteamAniName			= "Steam";
const float4					BossState_Damaged::SteamRenderScale	= float4{ 100.f, 100.f };

BossState_Damaged::BossState_Damaged()
{

}

BossState_Damaged::~BossState_Damaged()
{

}

void BossState_Damaged::Start()
{
	StreamResourceLoad();
	CreateStreamAni();
}


void BossState_Damaged::StreamResourceLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Monster");
	Dir.Move("Boss");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(SteamImagePath))->Cut(4, 1);
	IsLoad = true;
}

void BossState_Damaged::CreateStreamAni()
{
	AngrySteams.reserve(SteamCnt);

	for (size_t i = 0; i < SteamCnt; ++i)
	{
		GameEngineRender* RenderPtr = GetBoss()->CreateRender(RenderOrder::Monster2);
		RenderPtr->CreateAnimation
		({
			.AnimationName = SteamAniName,
			.ImageName = SteamImagePath,
			.Start = 0,
			.End = 3,
			.InterTimer = 0.1f,
			.Loop = false
		});

		RenderPtr->SetScale(SteamRenderScale);
		RenderPtr->SetPosition(StartOffset);
		RenderPtr->Off();

		float Angle = static_cast<float>((180 / (SteamCnt + 1)) * (i + 1));
		AngrySteams.push_back(std::make_pair(RenderPtr, Angle));
	}
}




void BossState_Damaged::EnterState()
{
	BossPhase NowPhase = BossHpBar::MainBossHP->GetPhase();
	switch (NowPhase)
	{
	case BossPhase::Normal:
		ChangeAniDir(BossMonster::AngryAniName);
		break;
	case BossPhase::Upset:
		ChangeAniDir(BossMonster::AngryAniName);
		//불눈 Render On
		break;
	case BossPhase::Rage:
		ChangeAniDir(BossMonster::RageAngryAniName);
		break;
	}

	for (std::pair<GameEngineRender*, const float>& Pair : AngrySteams)
	{
		GameEngineRender* AngrySteam = Pair.first;
		AngrySteam->On();
		AngrySteam->SetPosition(StartOffset);
		AngrySteam->ChangeAnimation(SteamAniName, true);
	}
}


void BossState_Damaged::Update(float _DeltaTime)
{
	if (true == CheckDamaged())
		return;

	if (false == SteamMove(_DeltaTime))
	{
		GetFSM()->ChangeState(BossStateType::DashToPlayer);
		return;
	}

	//플레이어와 충돌처리
	CheckCollisionWithPlayer();
}


bool BossState_Damaged::CheckDamaged()
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

bool BossState_Damaged::SteamMove(float _DeltaTime)
{
	static size_t AngryCount = 0;
	const size_t ChangeAngryCnt = 4;
	const float MoveSpeed = 1000.f;

	for (std::pair<GameEngineRender*, const float>& Pair : AngrySteams)
	{
		GameEngineRender* AngrySteam = Pair.first;
		const float MoveAngle = Pair.second;

		float4 Dir = float4::AngleToDirection2DToDeg(MoveAngle);
		Dir.y *= -1.f;
		AngrySteam->SetMove(Dir * MoveSpeed * _DeltaTime);

		float4 BossPos = GetBoss()->GetPos();

		if (false == AngrySteam->IsAnimationEnd())
			continue;

		++AngryCount;
		AngrySteam->SetPosition(StartOffset);
		AngrySteam->ChangeAnimation(SteamAniName, true);
	}

	//총 ChangeAngryCnt만큼 애니메이션이 재생됐다면 다음 State로 넘어가기 위해 false 리턴
	if ((ChangeAngryCnt * SteamCnt) <= AngryCount)
	{
		AngryCount = 0;
		return false;
	}

	return true;
}



void BossState_Damaged::ExitState()
{
	for (std::pair<GameEngineRender*, const float>& Pair: AngrySteams)
	{
		Pair.first->Off();
	}
}