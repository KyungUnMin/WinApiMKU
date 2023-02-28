#include "BossDeadEffect.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "BossMonster.h"
#include "ContentsEnum.h"


BossDeadEffect::BossDeadEffect()
{
}

BossDeadEffect::~BossDeadEffect()
{
}

void BossDeadEffect::Start()
{
	SettingRender();
	SettingPosition();
}

void BossDeadEffect::SettingRender()
{
	RenderPtr = CreateRender(RenderOrder::UI);
	const float4 RenderScale = float4{ 150.f, 150.f };
	const std::string_view AniName = "PopEffect";

	RenderPtr->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = BossMonster::LockBubbleImagePath,
		.Start = 1,
		.End = 5,
		.InterTimer = 0.1f,
		.Loop = false
		});

	RenderPtr->SetScale(RenderScale);
	RenderPtr->ChangeAnimation(AniName);
}

void BossDeadEffect::SettingPosition()
{
	float4 CenterPos = GameEngineWindow::GetScreenSize().half();
	float4 Offset = float4::Zero;
	Offset.x = GameEngineRandom::MainRandom.RandomFloat(-PosRadius, PosRadius);
	Offset.y = GameEngineRandom::MainRandom.RandomFloat(-PosRadius, PosRadius);

	SetPos(CenterPos + Offset);
}

void BossDeadEffect::Update(float _DeltaTime)
{
	if (false == RenderPtr->IsAnimationEnd())
		return;

	Death();
}





