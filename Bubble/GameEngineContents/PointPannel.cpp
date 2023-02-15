#include "PointPannel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "RoundLevelBase.h"
#include "ContentsEnum.h"
#include "TextLine.h"

PointPannel::PointPannel()
{

}

PointPannel::~PointPannel()
{

}

void PointPannel::Start()
{
	ResourceLoad();
	CreatePannel();
	CreateText();
}



void PointPannel::ResourceLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PointPannel.bmp"));

	IsLoad = true;
}

void PointPannel::CreatePannel()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	SetPos({ ScreenSize.hx(), OffsetY * 0.5f });
	GameEngineRender* RenderPtr = CreateRender("PointPannel.bmp", RenderOrder::UI);
	RenderPtr->SetScale({ ScreenSize.x, OffsetY });
	RenderPtr->SetAlpha(100);
}

void PointPannel::CreateText()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	const float4 TextScale = float4{ 20.f, 30.f };

	const std::pair<std::string, TextLineColor> Values[2][3] =
	{
		std::pair{"1UP", TextLineColor::Green},	std::pair{"HIGH SCORE", TextLineColor::Red},		std::pair{"Insert", TextLineColor::White},
		std::pair{"0", TextLineColor::White},			std::pair{"0", TextLineColor::White},					std::pair{"Coin", TextLineColor::White}
	};

	const float HeightPos[2] = { 25.f, 50.f };
	const float WidthPos[3] = { 200.f, 580.f, 760.f };

	for (size_t y = 0; y < 2; ++y)
	{
		for (size_t x = 0; x < 3; ++x)
		{
			Texts[y][x] = GetLevel()->CreateActor<TextLine>();

			if (0 == x)
				Texts[y][x]->SetAlign(TextAlignType::Left);
			else if(1 == x)
				Texts[y][x]->SetAlign(TextAlignType::Right);
			else if(2 == x)
				Texts[y][x]->SetAlign(TextAlignType::Center);

			Texts[y][x]->SetString(Values[y][x].first, Values[y][x].second);
			Texts[y][x]->SetScale(TextScale);
			Texts[y][x]->SetPos({ WidthPos[x], HeightPos[y] });
		}
	}
	

}



void PointPannel::Update(float _DeltaTime)
{
	AccTime += _DeltaTime;
	if (AccTime < ChangeTextTime)
		return;

	if (true == IsFirstText)
	{
		Texts[0][2]->SetString("Insert");
		Texts[1][2]->SetString("Coin");
	}
	else
	{
		Texts[0][2]->SetString("To");
		Texts[1][2]->SetString("START");
	}

	IsFirstText = !IsFirstText;
	AccTime = 0.f;
}
