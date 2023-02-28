#include "NavigationUI.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"
#include "TextLine.h"

const std::string_view NavigationUI::WorldImgPath	= "WorldClear.bmp";
const std::string_view NavigationUI::CourseImgPath	= "CourseSelect.bmp";

const std::string_view NavigationUI::TextValue[2] =
{
	"course select",
	"choose next round.",
};

NavigationUI::NavigationUI()
{

}

NavigationUI::~NavigationUI()
{
	
}


void NavigationUI::Start()
{
	ResourceLoad();
	CreateTexts();
	SetPos(GameEngineWindow::GetScreenSize().half());
}


void NavigationUI::ResourceLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("RoundRooms");
	Dir.Move("Reward");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(WorldImgPath));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(CourseImgPath));
	IsLoad = true;
}

void NavigationUI::CreateImage(NavigationType _ImgType)
{
	const float4 RenderScale = float4{ 900.f, 200.f };
	const float4 Offset = float4{ 0.f, -150.f };

	GameEngineRender* RenderPtr = nullptr;

	switch (_ImgType)
	{
	case NavigationType::CourseSelect:
		RenderPtr = CreateRender(CourseImgPath, RenderOrder::UI);
		break;
	case NavigationType::WorldClear:
		RenderPtr = CreateRender(WorldImgPath, RenderOrder::UI);
		break;
	}

	RenderPtr->SetScale(RenderScale);
	RenderPtr->SetPosition(Offset);
}

void NavigationUI::CreateTexts()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	float4 Offset = float4{ 0.f, -100.f };
	const float BetweenLen = 50.f;

	for (size_t i = 0; i < 2; ++i)
	{
		TextLine* Text = GetLevel()->CreateActor<TextLine>();
		Text->SetString(TextValue[i], TextLineColor::White);
		Text->SetScale(TextScale);
		Text->SetPos(ScreenSize.half() + Offset);
		Texts[i] = Text;
	}

	Texts[1]->SetMove(float4::Down * BetweenLen);
}




void NavigationUI::Update(float _DeltaTime)
{
	static float Timer = 0.f;
	const float SwitchTime = 0.25f;

	Timer += _DeltaTime;
	if (Timer < SwitchTime)
		return;

	Timer -= SwitchTime;
	for (size_t i = 0; i < 2; ++i)
	{
		Texts[i]->OnOffSwtich();
	}
}



void NavigationUI::Clear()
{
	for (size_t i = 0; i < 2; ++i)
	{
		Texts[i]->Death();
	}
}