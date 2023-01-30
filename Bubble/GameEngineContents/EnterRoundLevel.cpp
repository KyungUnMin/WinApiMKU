#include "EnterRoundLevel.h"
#include <string_view>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "SelectCharacterLevel.h"
#include "BackGround.h"
#include "EnterRoundCharater.h"
#include "TextLine.h"
#include "EnterRoundBubble.h"
#include "BubbleCore.h"

#include "RoundLevelBase.h"


const std::string		EnterRoundLevel::TextString[3] =
{
	"THE NEW ADVENTURE OF",
	"\"BUBBLE BOBBLE\"",
	"- THE NEXT GENERATION -",
};
const float				EnterRoundLevel::TextHeight[3] =
{
	50.f, 100.f, 150.f
};

EnterRoundLevel::EnterRoundLevel()
{

}

EnterRoundLevel::~EnterRoundLevel()
{

}

void EnterRoundLevel::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("TitleLevel");
	Dir.Move("EnterRoundLevel");

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("EnterRoundLevel_BackGround.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("EnterRoundLevel_Characters.bmp"))->Cut(4, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("EnterRoundLevel_ClearBubble.bmp"))->Cut(3, 1);
}



void EnterRoundLevel::Loading()
{
	ResourceLoad();

	BackGround* Back = CreateActor<BackGround>();
	Back->CreateRender("EnterRoundLevel_BackGround.bmp", EnterRoundRenderOrder::BackGround);

	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	BubbleSpawner = CreateActor<EnterRoundBubble>();

	CreateText();
}

void EnterRoundLevel::CreateText()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	const float4 TextScale = { 20.f, 30.f };
	for (size_t i = 0; i < 3; ++i)
	{
		TextLine* Text = CreateActor<TextLine>();
		Text->SetString(TextString[i], TextLineColor::Green);
		Text->SetPos({ ScreenSize.half().x, TextHeight[i] });
		Text->SetScale(TextScale);
	}

	TextLine* Text = CreateActor<TextLine>();
	Text->SetString("LET\'S TRY AND CHALLENGE!", TextLineColor::White);
	Text->SetPos({ ScreenSize.half().x, ScreenSize.y - 50.f });
	Text->SetScale(TextScale);
}


void EnterRoundLevel::Update(float _DeltaTime)
{
	AccTime += _DeltaTime;

	if (10.f < AccTime)
	{
		BubbleCore::GetInst().ChangeLevel("RoundAEnterLevel");
	}
}

void EnterRoundLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	AccTime = 0.f;
	BubbleSpawner->Reset();
	Player->Death();
	
	RoundLevelBase* RoundLevel = dynamic_cast<RoundLevelBase*>(_NextLevel);
	if (nullptr == RoundLevel)
	{
		MsgAssert("다음레벨은 RoundLevelBase를 상속받지 않았습니다");
		return;
	}

	RoundLevel->SetCharacter(SelectedCharater);
}

void EnterRoundLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Player = CreateActor<EnterRoundCharater>();
	Player->SetPos({ 100.f, 200.f });
	
	//디버깅용으로 이 레벨부터 시작했을땐 이전레벨이 존재하지 않음
	//임시로 기본캐릭터 지정
	if (nullptr == _PrevLevel)
	{
		Player->SetCharacter(0);
		return;
	}

	int CharacterIndex = dynamic_cast<SelectCharacterLevel*>(_PrevLevel)->GetSelectCharacter();
	Player->SetCharacter(CharacterIndex);

	SelectedCharater = static_cast<PlayerCharacterType>(CharacterIndex);
}

