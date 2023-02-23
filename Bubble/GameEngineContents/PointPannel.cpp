#include "PointPannel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "RoundLevelBase.h"
#include "ContentsEnum.h"
#include "TextLine.h"

unsigned int	PointPannel::NowPoint			= 0;
unsigned int	PointPannel::HighPoint			= 30000;
std::string		PointPannel::NowScoreStr		= "0";
std::string		PointPannel::HighScoreStr		= "30000";

void PointPannel::AddPoint(int _Score)
{
	NowPoint += _Score;
	if (HighPoint < NowPoint)
	{
		HighPoint = NowPoint;
	}

	char Buffer[10];

	NowScoreStr = std::to_string(NowPoint);
	HighScoreStr = std::to_string(HighPoint);
}

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
	const float OffsetY = 50.f;

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
		std::pair{"0", TextLineColor::White},			std::pair{HighScoreStr, TextLineColor::White},		std::pair{"Coin", TextLineColor::White}
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
	Update_Score();
	Update_2PText(_DeltaTime);
}


void PointPannel::Update_Score()
{
	TextLine* NowScoreText = Texts[1][0];
	TextLine* HighScoreText = Texts[1][1];

	NowScoreText->SetString(NowScoreStr);
	HighScoreText->SetString(HighScoreStr);
}

void PointPannel::Update_2PText(float _DeltaTime)
{
	static float AccTime = 0.0f;
	static bool IsFirstText = true;
	const float ChangeTextTime = 1.f;

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
