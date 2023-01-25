#include "RoundA1Level.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "BubbleCore.h"
#include "BackGround.h"


RoundA1Level::RoundA1Level()
{

}

RoundA1Level::~RoundA1Level()
{

}

void RoundA1Level::Loading()
{
	ResourceLoad();
	RoundLevelBase::LoadObstacle("A1", 6, 1);

	CreateBackGround();
	RoundLevelBase::CreateObstacle(float4::Down, RoundA1_RenderOrder::Obstacle);
	//RoundLevelBase::CreateObstacle(float4::Right, RoundA1_RenderOrder::Obstacle);
}

void RoundA1Level::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("RoundRooms");
	Dir.Move("RoundA");
	Dir.Move("RoundA1");

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RoundA1_BackGround.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RoundA1_BackEffect.bmp"))->Cut(3, 1);
}

void RoundA1Level::CreateBackGround()
{
	BackGround* Back = CreateActor<BackGround>();
	Back->RenderReserve(2);
	Back->CreateRender("RoundA1_BackGround.bmp", RoundA1_RenderOrder::BackGround);

	GameEngineRender* Effect = Back->CreateRender("RoundA1_BackEffect.bmp", RoundA1_RenderOrder::BackGround);
	Effect->CreateAnimation
	({
		.AnimationName = "Idle",
		.ImageName = "RoundA1_BackEffect.bmp",
		.Start = 0,
		.End = 2,
		.InterTimer = 0.15f
	});

	Effect->ChangeAnimation("Idle");
}


void RoundA1Level::Update(float _DeltaTime)
{
	RoundLevelBase::Update(_DeltaTime);

	if (false == GameEngineInput::IsAnyKey())
		return;
	
	if (true == RoundLevelBase::MoveToNextStage())
		return;

	if (false == RoundLevelBase::IsLastStage())
		return;

	BubbleCore::GetInst().ChangeLevel("EndingLevel");
}
