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


//(cpp파일에서 데이터를 수정하기 위해 static으로 둠, 그 외의 용도는 없음)
//TextLine을 통해 설명할 캐릭터 내용
const std::string SelectCharacterLevel::Description[5][4] =
{
	{"THE MOST",		"THE",				"THE ONE",		"THE ONE"},
	{"AVERAGE",		"FASTEST",		"WHOSE",			"WHOSE"},
	{"ONE OF",			"ONE OF",		"BUBBLES",		"BUBBLES"},
	{"THE BUNCH",		"THE FOUR",	"FLOAT THE",	"FLY THE"},
	{"",						"",						"FURTHEST",	"FASTEST"}
};

//캐릭터의 위치
const float4 SelectCharacterLevel::CharPos[4] =
{
	{100.f, 500.f},
	{320.f, 500.f},
	{570.f, 500.f},
	{800.f, 500.f},
};

//캐릭터 결정 여부
bool		SelectCharacterLevel::Selected			= false;


void SelectCharacterLevel::Loading()
{
	//리소스를 로드하는 private 함수
	ResourceLoad();

	//대각선으로 움직이는 뒤쪽 배경
	CreateActor<SelectCharacterBackGround>();

	//상단 글씨
	TopText = CreateActor<SelectCharacter_TopText>();

	//선택 아이콘
	SelectIcon = CreateActor<SelectCharacter_SelectIcon>();

	//캐릭터 생성
	CreateCharacters();

	//Text생성
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

		//캐릭터타입에 따라 초기화
		Characters[i]->SetCharacterType(static_cast<PlayerCharacterType>(i));
		Characters[i]->SetPos(CharPos[i]);
	}
}

//캐릭터 밑에 존재하는 캐릭터 설명 문구
void SelectCharacterLevel::CreateDescriptionText()
{
	float4 StartPos = float4{ 40.f, 550.f };
	float4 Gap = float4{ 240.f, 30.f };
	float4 NowPos = StartPos;

	//위치 설정
	for (size_t y = 0; y < 5; ++y)
	{
		for (size_t x = 0; x < 4; ++x)
		{
			//[4][0] or [4][1]의 경우 글씨를 만들지는 않고 NowPos값만 이동
			if (Description[y][x].empty())
			{
				NowPos.x += Gap.x;
				continue;
			}

			TextLine* Text = CreateActor<TextLine>();
			Text->SetString(Description[y][x]);

			//왼쪽 정렬
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
	//캐릭터 선택이 결정되지 않았다면 return
	if (false == Selected)
		return;

	//SelectIcon에 선택한 값이 존재함(이 부분은 나중에 수정이 필요함)
	int SelectIndex = SelectIcon->GetCurIndex();
	//선택한 캐릭터 'Select'애니메이션 재생
	Characters[SelectIndex]->Select();

	//캐릭터를 선택하고 3초뒤에 레벨 전환
	SelectTime += _DeltaTime;
	if (3.f < SelectTime)
	{
		BubbleCore::GetInst().ChangeLevel("EnterRoundLevel");
	}
}




//다음 씬에서, 이번 씬에 선택한 캐릭터가 무엇인지 알기위해 사용될 public 함수
int SelectCharacterLevel::GetSelectCharacter()
{
	return SelectIcon->GetCurIndex();
}

//이 레벨이 다른 레벨로 전환될 때 정리하고 나가기
void SelectCharacterLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	//선택여부 초기화
	Selected = false;

	//상단 타이머 초기화
	TopText->Reset();

	//캐릭터 애니메이션 초기화
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
