#include "GhostTracer.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"

const std::string_view	GhostTracer::RightImgPath		= "Right_Ghost.bmp";
const std::string_view	GhostTracer::LeftImgPath			= "Left_Ghost.bmp";
const std::string_view	GhostTracer::SmokeImgPath		= "GhostSmoke.bmp";

const std::string_view	GhostTracer::IdleAniName			= "Idle";
const std::string_view	GhostTracer::TraceAniName		= "Trace";

GhostTracer::GhostTracer()
{

}

GhostTracer::~GhostTracer()
{

}

void GhostTracer::Start()
{
	ResourceLoad();
	CreateComponent();


}



void GhostTracer::ResourceLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("NatureMissle");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightImgPath))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftImgPath))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(SmokeImgPath))->Cut(5, 1);
	IsLoad = true;
}

void GhostTracer::CreateComponent()
{
	const float4 RenderScale = float4{ 200.f, 200.f };
	const float4 CollisionScale = float4{ 50.f, 50.f };

	SmokeRender = CreateRender(RenderOrder::BossLockBubble);
	SmokeRender->SetScale(RenderScale);
	GhostRender = CreateRender(RenderOrder::Monster2);
	GhostRender->SetScale(RenderScale);

	CollisionPtr = CreateCollision(CollisionOrder::GhostTracer);
	CollisionPtr->SetScale(CollisionScale);
}

void GhostTracer::CreateAnimations()
{
	SmokeRender->CreateAnimation
	({
		.AnimationName = "Smoke",
		.ImageName = SmokeImgPath,
		.Start = 0,
		.End = 4,
		.Loop = false
	});

	std::string AniName;
	float Duration = 0.0f;

	Duration = 0.1f;
	AniName = MovableActor::RightStr + IdleAniName.data();
	GhostRender->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = RightImgPath,
		.Start = 2,
		.End = 3,
		.InterTimer = Duration,
		.Loop = true
	});


}


void GhostTracer::Update(float _DeltaTime)
{

}