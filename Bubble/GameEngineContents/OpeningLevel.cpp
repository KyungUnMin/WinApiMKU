#include "OpeningLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "BubbleCore.h"
#include "BackGround.h"
#include "OpeningSpotLight.h"
#include "OpeningMonster.h"
#include "OpeningPlayer.h"
#include "TextLine.h"


const float	OpeningLevel::CompanyLogoOffTime		= 3.f;
const float	OpeningLevel::SpotLightOutTime				= 7.f;
const float	OpeningLevel::SpotLightStopTime			= 9.f;
const float	OpeningLevel::SpotLightOffTime				= 10.f;
const float	OpeningLevel::BackCurtainUpStartTime	= 12.f;
const float	OpeningLevel::GameLogoOnTime				= 15.f;
const float	OpeningLevel::NextLevelChangeTime		= 18.f;


OpeningLevel::OpeningLevel()
{

}

OpeningLevel::~OpeningLevel()
{

}

void OpeningLevel::Loading()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("TitleLevel");
	Dir.Move("OpeningLevel");

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Opening_CompanyLogo.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Opening_SpotLight.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Opening_BackGround.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Opening_BackCurtain.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Opening_FrontCurtain.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Opening_Monster.bmp")) -> Cut(5, 47);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Opening_Player.bmp")) -> Cut(7, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Opening_GameLogo.bmp"));

	BackGround* BackImage = CreateActor<BackGround>();
	BackImage->RenderReserve(5);

	CompanyLogo = BackImage->CreateRender("Opening_CompanyLogo.bmp", OpeningRenderOrder::Logo);

	BackImage->CreateRender("Opening_BackGround.bmp", OpeningRenderOrder::BackGround);
	BackCurtain = BackImage->CreateRender("Opening_BackCurtain.bmp", OpeningRenderOrder::Curtain);
	BackImage->CreateRender("Opening_FrontCurtain.bmp", OpeningRenderOrder::Curtain);

	GameLogo = BackImage->CreateRender("Opening_GameLogo.bmp", OpeningRenderOrder::Logo);
	GameLogo->Off();
	GameLogo->SetPosition(GameLogo->GetPosition() + float4::Up * 70.f);

	GameEngineActor* Player = CreateActor<OpeningPlayer>();
	CreateActor<OpeningMonster>();
	
	OpeningSpotLight* SpotLight = CreateActor<OpeningSpotLight>();
	SpotLight->SetStopInfo(Player->GetPos(), SpotLightStopTime, SpotLightOutTime);
	this->SpotLight = SpotLight;

	TextLine* Text = nullptr;

	Text = CreateActor<TextLine>();
	Text->SetOwner(GameLogo);
	Text->SetPos(GameEngineWindow::GetScreenSize().half() + float4::Down * 260.f);
	Text->SetString("@ 1994 TAITO CORP. JAPAN");

	Text = CreateActor<TextLine>();
	Text->SetOwner(GameLogo);
	Text->SetPos(GameEngineWindow::GetScreenSize().half() + float4::Down * 300.f);
	Text->SetString("ALL RIGHTS RESERVED");
}

void OpeningLevel::Update(float _DeltaTime)
{
	AccTime += _DeltaTime;

	//if (true == GameEngineInput::IsAnyKey())
	if (NextLevelChangeTime < AccTime)
	{
		BubbleCore::GetInst().ChangeLevel("SelectPlayerLevel");
		return;
	}


	if (CompanyLogo->IsUpdate() && CompanyLogoOffTime < AccTime)
	{
		CompanyLogo->Off();
	}

	if (SpotLight->IsUpdate() && SpotLightOffTime < AccTime)
	{
		SpotLight->Off();
	}

	if (BackCurtainUpStartTime < AccTime)
	{
		float4 BackCurtainPos = BackCurtain->GetPosition();
		BackCurtainPos += float4::Up * 500.f * _DeltaTime;
		BackCurtain->SetPosition(BackCurtainPos);
	}

	if (false == GameLogo->IsUpdate() && GameLogoOnTime < AccTime)
	{
		GameLogo->On();
	}
}

void OpeningLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

}
