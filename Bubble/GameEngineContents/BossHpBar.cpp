#include "BossHpBar.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"
#include "ContentsDefine.h"

BossHpBar* BossHpBar::MainBossHP = nullptr;
const std::string_view BossHpBar::ImageName = "BossHp.bmp";

BossHpBar::BossHpBar()
{
	MainBossHP = this;
}

BossHpBar::~BossHpBar()
{
	if (this == MainBossHP)
	{
		MainBossHP = nullptr;
	}
}




void BossHpBar::Start()
{
	ResourceLoad();
	CreateHP();

	const float4 Pos = float4{ 70.f, 100.f };
	SetPos(Pos);
}



void BossHpBar::ResourceLoad()
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
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(ImageName));
	IsLoad = true;
}


void BossHpBar::CreateHP()
{
	const float4 BarPivot = float4{ 80.f, 110.f };
	const float4 HpOffset = float4{ 15.f, 0.f };
	const float4 RenderScale = float4{ 64.f, 64.f };

	HealthPoints.resize(NowHP + 1, nullptr);
	for (size_t i = 1; i < HealthPoints.size(); ++i)
	{
		HealthPoints[i] = CreateRender(ImageName, RenderOrder::UI);
		HealthPoints[i]->SetPosition(HpOffset * static_cast<float>(i));
		HealthPoints[i]->SetScale(RenderScale);
		HealthPoints[i]->Off();
	}
}


void BossHpBar::Update_Cheet()
{
	if (false == GameEngineInput::IsDown(CHEET_STAGE_CLEAR))
		return;

	const int CheetDamage = 6;
	if (NowHP <= CheetDamage)
		return;

	ExcuteDamage(CheetDamage);
}


void BossHpBar::Update(float _DeltaTime)
{
	Update_Cheet();

	static float Timer = 0.f;
	const float HpIncTime = 0.1f;

	if (NowHP < VisualHp)
		return;

	Timer += _DeltaTime;
	if (Timer < HpIncTime)
		return;

	Timer -= HpIncTime;
	HealthPoints[VisualHp++]->On();
}


bool BossHpBar::ExcuteDamage(int _Damage)
{
	const int UpsetPhazeHp = 20;
	const int RagePhazeHp = 10;

	//이미 죽은 몬스터는 데미지 처리 안함
	if (0 == NowHP)
		return false;

	//데미지 적용에 따른 Phase처리
	NowHP -= _Damage;
	if (NowHP < UpsetPhazeHp)
	{
		Phase = BossPhase::Upset;
	}
	if (NowHP < RagePhazeHp)
	{
		Phase = BossPhase::Rage;
	}

	//몬스터가 죽었다면
	if (NowHP <= 0)
	{
		NowHP = 0;

		for (size_t i = 1; i < HealthPoints.size(); ++i)
		{
			HealthPoints[i]->Off();
		}

		
		return true;
	}

	//몬스터가 아직 살아있을때 Hp바 처리
	for (size_t i = 1; i < HealthPoints.size(); ++i)
	{
		if (static_cast<int>(i) <= NowHP)
		{
			HealthPoints[i]->On();
		}
		else
		{
			HealthPoints[i]->Off();
		}
	}

	
	return false;
}


void BossHpBar::Revive()
{
	if (0 != NowHP)
	{
		MsgAssert("이 함수는 보스 몬스터가 Lock상태에 있을때만 사용할 수 있습니다");
		return;
	}

	const int ReviveHp = 3;
	NowHP = ReviveHp;

	for (size_t i = 1; i <= ReviveHp; ++i)
	{
		HealthPoints[i]->On();
	}
}
