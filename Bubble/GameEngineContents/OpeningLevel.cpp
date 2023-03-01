#include "OpeningLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "BubbleCore.h"
#include "BackGround.h"
#include "OpeningSpotLight.h"
#include "OpeningMonster.h"
#include "OpeningPlayer.h"
#include "TextLine.h"

const std::string_view OpeningLevel::BackCurtainImgPath		= "Opening_BackCurtain.bmp";
const std::string_view OpeningLevel::FrontCurtainImgPath		= "Opening_FrontCurtain.bmp";


//ó�� ȸ�� �ΰ� Off�Ǵ� �ð�
const float	OpeningLevel::CompanyLogoOffTime		= 3.f;

//����Ʈ ����Ʈ�� ������ ������ �ִ� �ð�
const float	OpeningLevel::SpotLightOutTime				= 10.f;

//����Ʈ ����Ʈ�� �����Ǵ� �ð�
const float	OpeningLevel::SpotLightStopTime			= 11.f;

//����Ʈ ����Ʈ�� ������ �ð�
const float	OpeningLevel::SpotLightOffTime				= 12.f;

//���� Ŀư�� �ö󰡴� �ð�
const float	OpeningLevel::BackCurtainUpStartTime	= 13.f;

//���� �ΰ� �ѱ�� �ð�
const float	OpeningLevel::GameLogoOnTime				= 19.f;

//���� ������ �̵��ϴ� �ð�
const float	OpeningLevel::NextLevelChangeTime		= 27.f;


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
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(BackCurtainImgPath));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(FrontCurtainImgPath));
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
	BackCurtain = BackImage->CreateRender(BackCurtainImgPath, OpeningRenderOrder::Curtain);
	BackImage->CreateRender(FrontCurtainImgPath, OpeningRenderOrder::Curtain);

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
	SoundPlayer = GameEngineResources::GetInst().SoundPlayerToControl("Opening.mp3");
	SoundPlayer.PauseOn();
}



void OpeningLevel::Update(float _DeltaTime)
{
	AccTime += _DeltaTime;

	if (true == GameEngineInput::IsAnyKey())
	{
		//Ư�� �ð��� ������ ���� ������ �̵�
		SoundPlayer.Stop();
		BubbleCore::GetInst().ChangeLevel("SelectPlayerLevel");
		return;
	}

	//if (true == GameEngineInput::IsAnyKey())
	if (NextLevelChangeTime < AccTime)
	{
		//Ư�� �ð��� ������ ���� ������ �̵�
		SoundPlayer.Stop();
		BubbleCore::GetInst().ChangeLevel("SelectPlayerLevel");
		return;
	}

	//CompanyLogoOffTime �ð��� ��������� ȸ�� �ΰ� ����
	if (CompanyLogo->IsUpdate() && CompanyLogoOffTime < AccTime)
	{
		CompanyLogo->Off();
		SoundPlayer.PauseOff();
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
