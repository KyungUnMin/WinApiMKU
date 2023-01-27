#include "RoundA1Level.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "BubbleCore.h"
#include "BackGround.h"
#include "ContentsEnum.h"
#include "PlayerBase.h"


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
	RoundLevelBase::CreateObstacle(float4::Down, RoundRenderOrder::Obstacle1);

	GameEngineInput::CreateKey("A1_NextStage", VK_F1);
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
	Back->CreateRender("RoundA1_BackGround.bmp", RoundRenderOrder::BackGround1);

	GameEngineRender* Effect = Back->CreateRender("RoundA1_BackEffect.bmp", RoundRenderOrder::BackGround2);
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
	
	if (false == GameEngineInput::IsDown("A1_NextStage"))
		return;

	if (true == RoundLevelBase::MoveToNextStage())
		return;

	if (false == RoundLevelBase::IsLastStage())
		return;

	BubbleCore::GetInst().ChangeLevel("EndingLevel");
}

void RoundA1Level::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	PlayerBase* Player = GetPlayer();
	Player->SetPos({ ScreenSize.x * 0.2f, ScreenSize.y * 0.8f });
}

void RoundA1Level::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	RoundLevelBase::LevelChangeEnd(_NextLevel);
	ArrangeStage(float4::Down, 0);
}

