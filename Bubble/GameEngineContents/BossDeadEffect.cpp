#include "BossDeadEffect.h"
#include <GameEngineCore/GameEngineRender.h>
#include "BossMonster.h"
#include "PointPannel.h"

BossDeadEffect::BossDeadEffect()
{

}

BossDeadEffect::~BossDeadEffect()
{

}

void BossDeadEffect::Start()
{
	PointPannel::AddPoint(KillPoint);

	SettingPointEffect();
	CreatePopEffect();
}


void BossDeadEffect::SettingPointEffect()
{
	SetMaxScale(MaxScale);
	SetMoveSpeed(MoveSpeed);

	const float4 PointRenderOffset = float4{ 0.f, -100.f };
	GameEngineRender* PointRender = CreateRender(BossMonster::KillPointImagePath , RenderOrder::UI);
	PointRender->SetPosition(PointRenderOffset);
	SetRender(PointRender);
}

void BossDeadEffect::CreatePopEffect()
{
	GameEngineRender* PopRender = CreateRender(RenderOrder::UI);
	const float4 RenderScale = float4{ 150.f, 150.f };
	const std::string_view AniName = "PopEffect";

	PopRender->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = BossMonster::LockBubbleImagePath,
		.Start = 1,
		.End = 5,
		.InterTimer = 0.2f,
		.Loop = false
	});

	PopRender->SetScale(RenderScale);
	PopRender->ChangeAnimation(AniName);
}



void BossDeadEffect::Update(float _DeltaTime)
{
	PointEffect::Update(_DeltaTime);

}
