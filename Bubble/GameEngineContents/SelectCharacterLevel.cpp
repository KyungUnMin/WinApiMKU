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
#include "ContentsEnum.h"


SelectCharacterLevel::SelectCharacterLevel()
{
}

SelectCharacterLevel::~SelectCharacterLevel()
{
}


//(cpp���Ͽ��� �����͸� �����ϱ� ���� static���� ��, �� ���� �뵵�� ����)
//TextLine�� ���� ������ ĳ���� ����
const std::string SelectCharacterLevel::Description[5][4] =
{
	{"THE MOST",		"THE",				"THE ONE",		"THE ONE"},
	{"AVERAGE",		"FASTEST",		"WHOSE",			"WHOSE"},
	{"ONE OF",			"ONE OF",		"BUBBLES",		"BUBBLES"},
	{"THE BUNCH",		"THE FOUR",	"FLOAT THE",	"FLY THE"},
	{"",						"",						"FURTHEST",	"FASTEST"}
};

//ĳ������ ��ġ
const float4 SelectCharacterLevel::CharPos[4] =
{
	{100.f, 500.f},
	{320.f, 500.f},
	{570.f, 500.f},
	{800.f, 500.f},
};

//ĳ���� ���� ����
bool		SelectCharacterLevel::Selected			= false;


void SelectCharacterLevel::Loading()
{
	//���ҽ��� �ε��ϴ� private �Լ�
	ResourceLoad();

	//�밢������ �����̴� ���� ���
	CreateActor<SelectCharacterBackGround>();

	//��� �۾�
	TopText = CreateActor<SelectCharacter_TopText>();

	//���� ������
	SelectIcon = CreateActor<SelectCharacter_SelectIcon>();

	//ĳ���� ����
	CreateCharacters();

	//Text����
	CreateDescriptionText();
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

	Dir.MoveParentToDirectory("Sound");
	Dir.Move("Sound");
	Dir.Move("BGM");
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("SelectCharacter.mp3"));
}


void SelectCharacterLevel::CreateCharacters()
{
	for (size_t i = 0; i < 4; ++i)
	{
		Characters[i] = CreateActor<SelectCharacter_Character>();

		//ĳ����Ÿ�Կ� ���� �ʱ�ȭ
		Characters[i]->SetCharacterType(static_cast<PlayerCharacterType>(i));
		Characters[i]->SetPos(CharPos[i]);
	}
}

//ĳ���� �ؿ� �����ϴ� ĳ���� ���� ����
void SelectCharacterLevel::CreateDescriptionText()
{
	float4 StartPos = float4{ 40.f, 550.f };
	float4 Gap = float4{ 240.f, 30.f };
	float4 NowPos = StartPos;

	//��ġ ����
	for (size_t y = 0; y < 5; ++y)
	{
		for (size_t x = 0; x < 4; ++x)
		{
			//[4][0] or [4][1]�� ��� �۾��� �������� �ʰ� NowPos���� �̵�
			if (Description[y][x].empty())
			{
				NowPos.x += Gap.x;
				continue;
			}

			TextLine* Text = CreateActor<TextLine>();
			Text->SetString(Description[y][x]);

			//���� ����
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
	//ĳ���� ������ �������� �ʾҴٸ� return
	if (false == Selected)
		return;

	//SelectIcon�� ������ ���� ������(�� �κ��� ���߿� ������ �ʿ���)
	int SelectIndex = SelectIcon->GetCurIndex();
	//������ ĳ���� 'Select'�ִϸ��̼� ���
	Characters[SelectIndex]->Select();

	//ĳ���͸� �����ϰ� 3�ʵڿ� ���� ��ȯ
	SelectTime += _DeltaTime;
	if (3.f < SelectTime)
	{
		BubbleCore::GetInst().ChangeLevel("EnterRoundLevel");
	}
}




//���� ������, �̹� ���� ������ ĳ���Ͱ� �������� �˱����� ���� public �Լ�
int SelectCharacterLevel::GetSelectCharacter()
{
	return SelectIcon->GetCurIndex();
}

//�� ������ �ٸ� ������ ��ȯ�� �� �����ϰ� ������
void SelectCharacterLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	//���ÿ��� �ʱ�ȭ
	Selected = false;

	//��� Ÿ�̸� �ʱ�ȭ
	TopText->Reset();

	//ĳ���� �ִϸ��̼� �ʱ�ȭ
	for (size_t i = 0; i < 4; ++i)
	{
		Characters[i]->Reset();
	}

	SelectTime = 0.f;
	SoundPlayer.Stop();
}

void SelectCharacterLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
	SoundPlayer = GameEngineResources::GetInst().SoundPlayerToControl("SelectCharacter.mp3");
}
