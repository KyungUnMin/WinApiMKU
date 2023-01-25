#include "RoundA2Level.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "BackGround.h"

RoundA2Level::RoundA2Level()
{

}

RoundA2Level::~RoundA2Level()
{

}



void RoundA2Level::Loading()
{
	ResourceLoad();
	RoundLevelBase::LoadObstacle("A2", 6, 1);

	CreateBackGround();
	RoundLevelBase::CreateObstacle(float4::Right, RoundA2_RenderOrder::Obstacle);
}


void RoundA2Level::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("RoundRooms");
	Dir.Move("RoundA");
	Dir.Move("RoundA2");

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RoundA2_BackGround1.bmp"))->Cut(4, 2);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RoundA2_BackGround2.bmp"))->Cut(2, 1);
}

void RoundA2Level::CreateBackGround()
{
	BackGround* Back = CreateActor<BackGround>();
	GameEngineRender* Render1 = Back->CreateRender("RoundA2_BackGround1.bmp", RoundA2_RenderOrder::BackGround);
	Render1->CreateAnimation
	({
		.AnimationName = "Idle",
		.ImageName = "RoundA2_BackGround1.bmp",
		.Start = 0,
		.End = 6,
		.InterTimer = 0.15f,
		});
	Render1->ChangeAnimation("Idle");

	GameEngineRender* Render2 = Back->CreateRender("RoundA2_BackGround2.bmp", RoundA2_RenderOrder::BackGround);
	Render2->CreateAnimation
	({
		.AnimationName = "Idle",
		.ImageName = "RoundA2_BackGround2.bmp",
		.Start = 0,
		.End = 1,
		.InterTimer = 0.25f,
		});
	Render2->ChangeAnimation("Idle");
}


void RoundA2Level::Update(float _DeltaTime)
{
	RoundLevelBase::Update(_DeltaTime);

	if (false == GameEngineInput::IsAnyKey())
		return;

	if (true == RoundLevelBase::MoveToNextStage())
		return;

	if (false == RoundLevelBase::IsLastStage())
		return;

	//다음 씬으로 이동
	int a = 10;
}

void RoundA2Level::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

}

void RoundA2Level::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

}