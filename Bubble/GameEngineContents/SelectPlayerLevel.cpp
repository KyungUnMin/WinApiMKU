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
	ResourceLoad();

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

void SelectPlayerLevel::ResourceLoad()
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
}



void SelectPlayerLevel::Update(float _DeltaTime)
{
	//아무 키라도 누르면 다음 씬으로 이동
	if (GameEngineInput::IsAnyKey())
	{
		BubbleCore::GetInst().ChangeLevel("SelectCharacterLevel");
		return;
	}

	//OnOffTime 시간마다 Text가 꺼졌다가 켜진다.
	accTime += _DeltaTime;
	if (accTime < 0.5f)
		return;

	accTime -= 0.5f;
	Text->OnOffSwtich();
}

