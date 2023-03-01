#include "EndingLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "TextLine.h"
#include "PointPannel.h"
#include "BackGround.h"
#include "OpeningLevel.h"

const std::string_view EndingLevel::BGIPath = "EndingBGI.bmp";

EndingLevel::EndingLevel()
{
}

EndingLevel::~EndingLevel()
{
}

void EndingLevel::Loading()
{
	LoadBGI();
	LoadBGM();

	BgmCtrl = GameEngineResources::GetInst().SoundPlayerToControl("Ending.mp3");
	BgmCtrl.PauseOn();
	ImageCreate();
}



void EndingLevel::LoadBGI()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("EndingLevel");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(BGIPath));
	IsLoad = true;
}

void EndingLevel::LoadBGM()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");
	Dir.Move("BGM");
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Ending.mp3"));
	IsLoad = true;
}


void EndingLevel::ImageCreate()
{
	BackImg = CreateActor<BackGround>();
	BackImg->RenderReserve(3);

	BackImg->CreateRender(BGIPath, EndingRenderOrder::BackGround);
	BackImg->CreateRender(OpeningLevel::BackCurtainImgPath, EndingRenderOrder::BackCurtain)->Off();
	BackImg->CreateRender(OpeningLevel::FrontCurtainImgPath, EndingRenderOrder::FrontCurtain)->Off();
}





void EndingLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BgmCtrl.PauseOff();
	PlayerScore = PointPannel::GetNowPoint();
	PointPannel::PointClear();
}


void EndingLevel::Update(float _DeltaTime)
{

}

void EndingLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BgmCtrl.PauseOn();
}







/*
	ScreenSize = GameEngineWindow::GetScreenSize();

	TextLine* Text = CreateActor<TextLine>();
	Text->SetPos(ScreenSize.half());
	Text->SetScale({30.f, 50.f});
	Text->SetString("Thank You For Playing", TextLineColor::Gold);

	Text = CreateActor<TextLine>();
	Text->SetPos(ScreenSize.half() + float4::Down * 100.f);
	Text->SetScale({ 20.f, 30.f });
	Text->SetString("Press \'R\' To Restart", TextLineColor::Red);

	GameEngineInput::CreateKey("ReStart", 'R');

	if (true == GameEngineInput::IsDown("ReStart"))
		BubbleCore::GetInst().ChangeLevel("SelectCharacterLevel");
*/