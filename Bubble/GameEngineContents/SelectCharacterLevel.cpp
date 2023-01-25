#include "SelectCharacterLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include "BubbleCore.h"
#include "TextLine.h"
#include "SelectCharacterBackGround.h"
#include "SelectCharacter_TopText.h"
#include "SelectCharacter_Character.h"
#include "SelectCharacter_SelectIcon.h"

const std::string SelectCharacterLevel::Description[5][4] =
{
	{"THE MOST",		"THE",				"THE ONE",		"THE ONE"},
	{"AVERAGE",		"FASTEST",		"WHOSE",			"WHOSE"},
	{"ONE OF",			"ONE OF",		"BUBBLES",		"BUBBLES"},
	{"THE BUNCH",		"THE FOUR",	"FLOAT THE",	"FLY THE"},
	{"",						"",						"FURTHEST",	"FASTEST"}
};

const float4 SelectCharacterLevel::CharPos[4] =
{
	{100.f, 500.f},
	{320.f, 500.f},
	{570.f, 500.f},
	{800.f, 500.f},
};

bool		SelectCharacterLevel::Selected			= false;


SelectCharacterLevel::SelectCharacterLevel()
{

}

SelectCharacterLevel::~SelectCharacterLevel()
{

}

void SelectCharacterLevel::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("TitleLevel");
	Dir.Move("CharacterSelectLevel");

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SelectCharacter_CheckPattern.bmp"));

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SelectCharacter_PlayerSelectText.bmp"))->Cut(12, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SelectCharacter_Bubble.bmp"))->Cut(6, 1);

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SelectCharacter_Numbers.bmp"))->Cut(10, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SelectCharacter_TimeText.bmp"))->Cut(4, 1);

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SelectCharacter_Characters.bmp"))->Cut(4, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SelectCharacter_CharacterName.bmp"))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SelectCharacter_NoticeHandle.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SelectCharacter_ClearBubble.bmp"))->Cut(3, 1);

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SelectCharacte_SelectIcon.bmp"));
}

void SelectCharacterLevel::Loading()
{
	ResourceLoad();


	CreateActor<SelectCharacterBackGround>();
	CreateActor<SelectCharacter_TopText>();
	SelectIcon = CreateActor<SelectCharacter_SelectIcon>();

	CreateCharacters();
	CreateDescriptionText();
}

void SelectCharacterLevel::CreateCharacters()
{
	for (size_t i = 0; i < 4; ++i)
	{
		Characters[i] = CreateActor<SelectCharacter_Character>();
		Characters[i]->SetCharacterType(static_cast<SelectCharacter_Character::CharacterType>(i));
		Characters[i]->SetPos(CharPos[i]);
	}
}

void SelectCharacterLevel::CreateDescriptionText()
{
	float4 StartPos = float4{ 40.f, 550.f };
	float4 Gap = float4{ 240.f, 30.f };
	float4 NowPos = StartPos;

	for (size_t y = 0; y < 5; ++y)
	{
		for (size_t x = 0; x < 4; ++x)
		{
			if (Description[y][x].empty())
			{
				NowPos.x += Gap.x;
				continue;
			}

			TextLine* Text = CreateActor<TextLine>();
			Text->SetString(Description[y][x]);
			Text->OnLeftAlign();
			Text->SetScale({ 23.f, 30.f });
			Text->SetPos(NowPos);
			NowPos.x += Gap.x;
		}

		NowPos.x = StartPos.x;
		NowPos.y += Gap.y;
	}
}


void SelectCharacterLevel::Update(float _DeltaTime)
{
	if (false == Selected)
		return;

	int SelectIndex = SelectIcon->GetCurIndex();
	Characters[SelectIndex]->Select();

	SelectTime += _DeltaTime;
	if (3.f < SelectTime)
	{
		BubbleCore::GetInst().ChangeLevel("EnterRoundLevel");
	}
}

void SelectCharacterLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

}

void SelectCharacterLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{

}


int SelectCharacterLevel::GetSelectCharacter()
{
	return SelectIcon->GetCurIndex();
}
