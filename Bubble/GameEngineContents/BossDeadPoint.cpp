#include "BossDeadPoint.h"
#include <GameEngineCore/GameEngineRender.h>
#include "BossMonster.h"
#include "PointPannel.h"

BossDeadPoint::BossDeadPoint()
{

}

BossDeadPoint::~BossDeadPoint()
{

}

void BossDeadPoint::Start()
{
	PointPannel::AddPoint(KillPoint);

	PointEffect::SetMaxScale(MaxScale);
	PointEffect::SetMoveSpeed(MoveSpeed);

	const float4 PointRenderOffset = float4{ 0.f, -100.f };
	GameEngineRender* PointRender = CreateRender(BossMonster::KillPointImagePath, RenderOrder::UI);
	PointRender->SetPosition(PointRenderOffset);
	SetRender(PointRender);
}

void BossDeadPoint::Update(float _DeltaTime)
{
	PointEffect::Update(_DeltaTime);

}
