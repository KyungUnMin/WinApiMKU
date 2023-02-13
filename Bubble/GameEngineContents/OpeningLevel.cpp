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


//처음 회사 로고 Off되는 시간
const float	OpeningLevel::CompanyLogoOffTime		= 3.f;

//스포트 라이트가 밖으로 나갈수 있는 시간
const float	OpeningLevel::SpotLightOutTime				= 7.f;

//스포트 라이트가 고정되는 시간
const float	OpeningLevel::SpotLightStopTime			= 9.f;

//스포트 라이트가 꺼지는 시간
const float	OpeningLevel::SpotLightOffTime				= 10.f;

//뒤쪽 커튼이 올라가는 시간
const float	OpeningLevel::BackCurtainUpStartTime	= 12.f;

//게임 로고 켜기는 시간
const float	OpeningLevel::GameLogoOnTime				= 15.f;

//다음 씬으로 이동하는 시간
const float	OpeningLevel::NextLevelChangeTime		= 18.f;


OpeningLevel::OpeningLevel()
{

}

OpeningLevel::~OpeningLevel()
{

}



void OpeningLevel::Loading()
{
	ResourceLoad();
	SoundPlay();
	CreateBackGround();

	GameEngineActor* Player = CreateActor<OpeningPlayer>();
	CreateActor<OpeningMonster>();
	
	OpeningSpotLight* SpotLight = CreateActor<OpeningSpotLight>();
	SpotLight->SetStopInfo(Player->GetPos(), SpotLightStopTime, SpotLightOutTime);
	this->SpotLight = SpotLight;

	CreateText();
}


void OpeningLevel::ResourceLoad()
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
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Opening_Monster.bmp"))->Cut(5, 47);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Opening_Player.bmp"))->Cut(7, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Opening_GameLogo.bmp"));
}



void OpeningLevel::CreateBackGround()
{
	BackGround* BackImage = CreateActor<BackGround>();
	BackImage->RenderReserve(5);

	CompanyLogo = BackImage->CreateRender("Opening_CompanyLogo.bmp", OpeningRenderOrder::Logo);

	BackImage->CreateRender("Opening_BackGround.bmp", OpeningRenderOrder::BackGround);
	BackCurtain = BackImage->CreateRender("Opening_BackCurtain.bmp", OpeningRenderOrder::Curtain);
	BackImage->CreateRender("Opening_FrontCurtain.bmp", OpeningRenderOrder::Curtain);

	GameLogo = BackImage->CreateRender("Opening_GameLogo.bmp", OpeningRenderOrder::Logo);
	GameLogo->Off();
	GameLogo->SetPosition(GameLogo->GetPosition() + float4::Up * 70.f);
}


void OpeningLevel::CreateText()
{
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

void OpeningLevel::SoundPlay()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");
	Dir.Move("BGM");

	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Opening.mp3"));
	SoundPtr = &GameEngineResources::GetInst().SoundPlayerToControl("Opening.mp3");
	SoundPtr->PauseOn();
}



void OpeningLevel::Update(float _DeltaTime)
{
	AccTime += _DeltaTime;

	//if (true == GameEngineInput::IsAnyKey())
	if (NextLevelChangeTime < AccTime)
	{
		//특정 시간이 지나면 다음 씬으로 이동
		BubbleCore::GetInst().ChangeLevel("SelectPlayerLevel");
		return;
	}

	//CompanyLogoOffTime 시간이 경과했으면 회사 로고 끄기
	if (CompanyLogo->IsUpdate() && CompanyLogoOffTime < AccTime)
	{
		CompanyLogo->Off();
		SoundPtr->PauseOff();
	}

	//SpotLightOffTime 시간이 경과했으면 스포트 라이트 끄기
	if (SpotLight->IsUpdate() && SpotLightOffTime < AccTime)
	{
		SpotLight->Off();
	}

	//BackCurtainUpStartTime 시간이 경과했으면 뒤쪽 커튼 위로 올리기
	if (BackCurtainUpStartTime < AccTime)
	{
		float4 BackCurtainPos = BackCurtain->GetPosition();
		BackCurtainPos += float4::Up * 500.f * _DeltaTime;
		BackCurtain->SetPosition(BackCurtainPos);
	}

	//GameLogoOnTime 시간이 경과했으면 게임 로고 띄우기
	if (false == GameLogo->IsUpdate() && GameLogoOnTime < AccTime)
	{
		GameLogo->On();
	}
}
