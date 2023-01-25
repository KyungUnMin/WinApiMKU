#include "RoundA3Level.h"
#include <vector>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "BackGround.h"

RoundA3Level::RoundA3Level()
{

}

RoundA3Level::~RoundA3Level()
{

}

void RoundA3Level::Loading()
{
	ResourceLoad();
	RoundLevelBase::LoadObstacle("A3", 6, 1);

	CreateBackGround();
	RoundLevelBase::CreateObstacle(float4::Right, RoundA3_RenderOrder::Obstacle);
}

void RoundA3Level::Update(float _DeltaTime)
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

void RoundA3Level::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

void RoundA3Level::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}


void RoundA3Level::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("RoundRooms");
	Dir.Move("RoundA");
	Dir.Move("RoundA3");

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RoundA3_BackGround1.bmp"))->Cut(5, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RoundA3_BackGround2.bmp"))->Cut(3, 1);
}

void RoundA3Level::CreateBackGround()
{
	BackGround* Back = CreateActor<BackGround>();
	Back->RenderReserve(2);

	GameEngineRender* Render1 = Back->CreateRender("RoundA3_BackGround1.bmp", RoundA3_RenderOrder::BackGround);

	Render1->CreateAnimation
	({
		.AnimationName = "Idle",
		.ImageName = "RoundA3_BackGround1.bmp",
		.InterTimer = 0.2f,
		.FrameIndex = std::vector<int> { 0, 1, 2, 3, 4, 3 },
	});
	Render1->ChangeAnimation("Idle");

	GameEngineRender* Render2 = Back->CreateRender("RoundA3_BackGround2.bmp", RoundA3_RenderOrder::BackGround);
	Render2->CreateAnimation
	({
		.AnimationName = "Idle",
		.ImageName = "RoundA3_BackGround2.bmp",
		.InterTimer = 0.2f,
		.FrameIndex = std::vector<int> { 0, 1, 2, 1 }
	});
	Render2->ChangeAnimation("Idle");
}
