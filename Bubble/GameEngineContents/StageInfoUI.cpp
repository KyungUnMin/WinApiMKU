#include "StageInfoUI.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "RoundLevelBase.h"
#include "TextLine.h"

StageInfoUI::StageInfoUI()
{

}

StageInfoUI::~StageInfoUI()
{

}



void StageInfoUI::Start()
{
	float4 CenterPos = GameEngineWindow::GetScreenSize().half();
	float4 Offset = float4{ 0.f, 50.f };

	for (size_t i = 0; i < 3; ++i)
	{
		TextLine* Text = GetLevel()->CreateActor<TextLine>();
		Text->SetScale(TextScale);
		Text->SetPos(CenterPos + Offset);
		Texts[i] = Text;
	}

	Texts[0]->SetMove(float4::Up * TextScale * 2.f);
	Texts[1]->SetMove(float4::Up * TextScale);
	Texts[2]->SetMove(float4::Down * TextScale * 2.f);

	Texts[0]->SetColor(TextLineColor::White);
	Texts[1]->SetColor(TextLineColor::Green);
	Texts[2]->SetString("Start !", TextLineColor::White);
}


void StageInfoUI::On()
{
	GameEngineObject::On();
	Timer = 0.f;
	SettingTextValue();
}



void StageInfoUI::SettingTextValue()
{
	if (StageInfoType::UNKNOWN == Info)
	{
		MsgAssert("SetInfo 함수를 호출시켜주어야 합니다");
		return;
	}

	if (true == RoundLevel->IsLastStage() && StageInfoType::AEnter != Info)
		return;

	size_t FirstStageIdx = (StageInfoType::AEnter == Info) ? 1 : 2;

	size_t NowStage = RoundLevel->GetNowStage();
	size_t StageNum = NowStage + FirstStageIdx;

	std::string StageNumStr = "Round A-" + std::to_string(StageNum);
	Texts[0]->SetString(StageNumStr);

	const std::string_view& StageName = LevelInfoData[static_cast<size_t>(Info)][NowStage];
	Texts[1]->SetString(StageName);

	for (size_t i = 0; i < 3; ++i)
	{
		Texts[i]->On();
	}
}










void StageInfoUI::Update(float _DeltaTime)
{
	Timer += _DeltaTime;
	if (Timer < OffTime)
		return;

	Off();
}



void StageInfoUI::Off()
{
	GameEngineObject::Off();
	for (size_t i = 0; i < 3; ++i)
	{
		Texts[i]->Off();
	}
}