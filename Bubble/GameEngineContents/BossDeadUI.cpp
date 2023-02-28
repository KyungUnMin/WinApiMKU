#include "BossDeadUI.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"
#include "TextLine.h"

const std::string_view BossDeadUI::ImagePath = "WorldClear.bmp";

const std::string_view BossDeadUI::TextValue[2] =
{
	"course select",
	"choose next round.",
};

BossDeadUI::BossDeadUI()
{

}

BossDeadUI::~BossDeadUI()
{
	
}


void BossDeadUI::Start()
{
	ResourceLoad();

	CreateImage();
	CreateTexts();

	SetPos(GameEngineWindow::GetScreenSize().half());
}


void BossDeadUI::ResourceLoad()
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
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(ImagePath));
	IsLoad = true;
}

void BossDeadUI::CreateImage()
{
	const float4 RenderScale = float4{ 900.f, 200.f };
	const float4 Offset = float4{ 0.f, -150.f };

	GameEngineRender* RenderPtr = CreateRender(ImagePath, RenderOrder::UI);
	RenderPtr->SetScale(RenderScale);
	RenderPtr->SetPosition(Offset);
}

void BossDeadUI::CreateTexts()
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




void BossDeadUI::Update(float _DeltaTime)
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



void BossDeadUI::Clear()
{
	for (size_t i = 0; i < 2; ++i)
	{
		Texts[i]->Death();
	}
}