#include "TitleLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
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

	//Dir.MoveParentToDirectory("Common");
	//Dir.Move("Common");
	//GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Text.bmp"));

	GameEngineInput::CreateKey("NextLevel", 'P');

	CreateActor<TitleBackGround>();
	CreateActor<TextLine>();
	CreateActor<TextLine>();

	TextLine::Reserve(2);
	TextLine::GetText(0)->SetScale({20.f , 20.f});
	TextLine::GetText(0)->SetString("Hello World", TextLineColor::White);
	TextLine::GetText(0)->SetPos({ 200.f, 200.f });

	TextLine::GetText(1)->SetScale({ 20.f , 20.f });
	TextLine::GetText(1)->SetString("Bye World", TextLineColor::Gold);
	TextLine::GetText(1)->SetPos({ 400.f, 400.f });
}

void TitleLevel::Update(float _DeltaTime)
{
	if (false == GameEngineInput::IsDown("NextLevel"))
		return;


	BubbleCore::GetInst().ChangeLevel("State01");
}

void TitleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	TextLine::Release();
}
