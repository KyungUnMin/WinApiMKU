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


//ó�� ȸ�� �ΰ� Off�Ǵ� �ð�
const float	OpeningLevel::CompanyLogoOffTime		= 3.f;

//����Ʈ ����Ʈ�� ������ ������ �ִ� �ð�
const float	OpeningLevel::SpotLightOutTime				= 7.f;

//����Ʈ ����Ʈ�� �����Ǵ� �ð�
const float	OpeningLevel::SpotLightStopTime			= 9.f;

//����Ʈ ����Ʈ�� ������ �ð�
const float	OpeningLevel::SpotLightOffTime				= 10.f;

//���� Ŀư�� �ö󰡴� �ð�
const float	OpeningLevel::BackCurtainUpStartTime	= 12.f;

//���� �ΰ� �ѱ�� �ð�
const float	OpeningLevel::GameLogoOnTime				= 15.f;

//���� ������ �̵��ϴ� �ð�
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
		//Ư�� �ð��� ������ ���� ������ �̵�
		BubbleCore::GetInst().ChangeLevel("SelectPlayerLevel");
		return;
	}

	//CompanyLogoOffTime �ð��� ��������� ȸ�� �ΰ� ����
	if (CompanyLogo->IsUpdate() && CompanyLogoOffTime < AccTime)
	{
		CompanyLogo->Off();
		SoundPtr->PauseOff();
	}

	//SpotLightOffTime �ð��� ��������� ����Ʈ ����Ʈ ����
	if (SpotLight->IsUpdate() && SpotLightOffTime < AccTime)
	{
		SpotLight->Off();
	}

	//BackCurtainUpStartTime �ð��� ��������� ���� Ŀư ���� �ø���
	if (BackCurtainUpStartTime < AccTime)
	{
		float4 BackCurtainPos = BackCurtain->GetPosition();
		BackCurtainPos += float4::Up * 500.f * _DeltaTime;
		BackCurtain->SetPosition(BackCurtainPos);
	}

	//GameLogoOnTime �ð��� ��������� ���� �ΰ� ����
	if (false == GameLogo->IsUpdate() && GameLogoOnTime < AccTime)
	{
		GameLogo->On();
	}
}
