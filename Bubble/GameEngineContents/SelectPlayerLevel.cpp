#include "SelectPlayerLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "TextLine.h"
#include "ContentsEnum.h"


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
	Dir.Move("PlayerSelectLevel");

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("CheckPattern.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("1p.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("2p.bmp"));

	CreateActor<TextLine>();
	Text = TextLine::GetText(0);
	Text->SetString("PUSH     OR     SELECT BUTTON", TextLineColor::White);
	Text->SetScale({ 20.f, 30.f });
	Text->SetPos(GameEngineWindow::GetScreenSize().half());

	GameEngineRender* Render1P = Text->CreateRender("1p.bmp", RenderOrder::UI);
	GameEngineRender* Render2P = Text->CreateRender("2p.bmp", RenderOrder::UI);

	Render1P->SetScale({ 60.f, 50.f });
	Render2P->SetScale({ 60.f, 50.f });

	Render1P->SetPosition(float4::Left * 170.f);
	Render2P->SetPosition(float4::Left * 30.f);

	Render1P->SetParent(Text);
	Render2P->SetParent(Text);
}

void SelectPlayerLevel::Update(float _DeltaTime)
{
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
