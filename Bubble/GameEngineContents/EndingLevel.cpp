#include "EndingLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "TextLine.h"
#include "PointPannel.h"
#include "BackGround.h"
#include "BubbleCore.h"

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

	CreateActor<BackGround>()->CreateRender(BGIPath);
	CreateText();

	GameEngineInput::CreateKey("ReStart", 'R');
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
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("OriginThema.mp3"));
	IsLoad = true;
}



void EndingLevel::CreateText()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	TextLine* Text = CreateActor<TextLine>();
	Text->SetPos(ScreenSize.half());
	Text->SetScale({ 30.f, 50.f });
	Text->SetString("Thank You For Playing", TextLineColor::Gold);

	Text = CreateActor<TextLine>();
	Text->SetPos(ScreenSize.half() + float4::Down * 100.f);
	Text->SetScale({ 20.f, 30.f });
	Text->SetString("Press \'R\' To Restart", TextLineColor::Red);

	ScoreText = CreateActor<TextLine>();
	ScoreText->SetPos(ScreenSize.half() + float4::Down * 250.f);
	ScoreText->SetScale({ 20.f, 30.f });
}







void EndingLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	std::string TextValue = "your score : " + std::to_string(PointPannel::GetNowPoint());
	ScoreText->SetString(TextValue, TextLineColor::Sky);
	PointPannel::PointClear();

	BgmCtrl = GameEngineResources::GetInst().SoundPlayerToControl("OriginThema.mp3");
}


void EndingLevel::Update(float _DeltaTime)
{
	if (false == GameEngineInput::IsDown("ReStart"))
		return;

	BubbleCore::GetInst().ChangeLevel("SelectCharacterLevel");
}

void EndingLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BgmCtrl.Stop();
}

