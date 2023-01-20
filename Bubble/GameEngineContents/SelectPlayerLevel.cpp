#include "SelectPlayerLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "TextLine.h"
#include "BackGround.h"
#include "BubbleCore.h"


SelectPlayerLevel::SelectPlayerLevel()
{

}

SelectPlayerLevel::~SelectPlayerLevel()
{

}

void SelectPlayerLevel::Loading()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("TitleLevel");
	Dir.Move("PlayerSelectLevel");

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerSelect_CheckPattern.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerSelect_1p.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerSelect_2p.bmp"));

	BackGround* BackGroundImage = CreateActor<BackGround>();
	BackGroundImage->CreateRender("PlayerSelect_CheckPattern.bmp", SelectPlayerLevelRenderOrder::BackGround);

	Text = CreateActor<TextLine>();
	Text->SetString("PUSH     OR     SELECT BUTTON", TextLineColor::White);
	Text->SetPos(GameEngineWindow::GetScreenSize().half());
	Text->SetScale({ 20.f, 30.f });
	
	GameEngineRender* Render1P = Text->CreateRender("PlayerSelect_1p.bmp", SelectPlayerLevelRenderOrder::UI);
	GameEngineRender* Render2P = Text->CreateRender("PlayerSelect_2p.bmp", SelectPlayerLevelRenderOrder::UI);

	Render1P->SetScale({ 60.f, 50.f });
	Render2P->SetScale({ 60.f, 50.f });

	Render1P->SetPosition(float4::Left * 170.f);
	Render2P->SetPosition(float4::Left * 30.f);
}

void SelectPlayerLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsAnyKey())
	{
		BubbleCore::GetInst().ChangeLevel("SelectCharacterLevel");
		return;
	}

	accTime += _DeltaTime;
	if (accTime < 0.5f)
		return;

	accTime -= 0.5f;
	Text->OnOffSwtich();
}


void SelectPlayerLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{

}


void SelectPlayerLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

}
