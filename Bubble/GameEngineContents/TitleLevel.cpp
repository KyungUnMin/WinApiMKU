#include "TitleLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "TitleBackGround.h"
#include "BubbleCore.h"
#include "TextLine.h"

TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::Loading()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("TitleLevel");

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BackGround.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BackCurtain.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FrontCurtain.bmp"));

	CreateActor<TitleBackGround>();
	CreateActor<TextLine>();
	CreateActor<TextLine>();

	TextLine::Reserve(2);
	TextLine::GetText(0)->SetScale({20.f , 40.f});
	TextLine::GetText(0)->SetString("[Insetout's blog]", TextLineColor::White);
	TextLine::GetText(0)->SetPos(GameEngineWindow::GetScreenSize().half() + float4{0.f, -50.f});

	TextLine::GetText(1)->SetScale({ 20.f , 40.f });
	TextLine::GetText(1)->SetString("Welcome!", TextLineColor::Gold);
	TextLine::GetText(1)->SetPos(GameEngineWindow::GetScreenSize().half() + float4{0.f, 50.f});
}

void TitleLevel::Update(float _DeltaTime)
{
	if (false == GameEngineInput::IsAnyKey())
		return;

	BubbleCore::GetInst().ChangeLevel("State01");
}

void TitleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	TextLine::Release();
}
