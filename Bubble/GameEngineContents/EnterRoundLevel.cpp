#include "EnterRoundLevel.h"
#include <string_view>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "SelectCharacterLevel.h"
#include "BackGround.h"
#include "EnterRoundCharater.h"
#include "TextLine.h"
#include "EnterRoundBubble.h"
#include "BubbleCore.h"

#include "RoundLevelBase.h"


//화면 최상단 텍스트 내용
const std::string		EnterRoundLevel::TextString[3] =
{
	"THE NEW ADVENTURE OF",
	"\"BUBBLE BOBBLE\"",
	"- THE NEXT GENERATION -",
};

//화면 최상단 텍스트 오프셋
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

	Dir.MoveParentToDirectory("Sound");
	Dir.Move("Sound");
	Dir.Move("BGM");
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("EnterRound.mp3"));
}



void EnterRoundLevel::Loading()
{
	//리소스 로드하는 private 함수
	ResourceLoad();

	//백그라운드 배경(우주)
	BackGround* Back = CreateActor<BackGround>();
	Back->CreateRender("EnterRoundLevel_BackGround.bmp", EnterRoundRenderOrder::BackGround);

	//투명 거품을 생성하는 스포너 Actor생성
	BubbleSpawner = CreateActor<EnterRoundBubble>();

	CreateText();
}

void EnterRoundLevel::CreateText()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	//상단 텍스트
	const float4 TextScale = { 20.f, 30.f };
	for (size_t i = 0; i < 3; ++i)
	{
		TextLine* Text = CreateActor<TextLine>();
		Text->SetString(TextString[i], TextLineColor::Green);
		Text->SetPos({ ScreenSize.half().x, TextHeight[i] });
		Text->SetScale(TextScale);
	}

	//하단 텍스트
	TextLine* Text = CreateActor<TextLine>();
	Text->SetString("LET\'S TRY AND CHALLENGE!", TextLineColor::White);
	Text->SetPos({ ScreenSize.half().x, ScreenSize.y - 50.f });
	Text->SetScale(TextScale);
}

//이 레벨로 전환됐을때 호출
void EnterRoundLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	//이때 플레이어 생성
	Player = CreateActor<EnterRoundCharater>();
	Player->SetPos({ 100.f, 200.f });

	//디버깅용으로 이 레벨부터 시작했을땐 이전레벨이 존재하지 않음(임시로 기본캐릭터 지정)
	if (nullptr == _PrevLevel)
	{
		Player->SetCharacter(0);
		return;
	}

	//이전 레벨(SelectCharacterLevel)에서 선택한 플레이어의 정보를 받아와서 방금 생성한 플레이어에 적용
	int CharacterIndex = dynamic_cast<SelectCharacterLevel*>(_PrevLevel)->GetSelectCharacter();
	Player->SetCharacter(CharacterIndex);

	//SelectedCharater  : 이번에 선택한 캐릭터
	SelectedCharater = static_cast<PlayerCharacterType>(CharacterIndex);

	SoundPlayer = GameEngineResources::GetInst().SoundPlayerToControl("EnterRound.mp3");
}

void EnterRoundLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsAnyKey())
	{
		SoundPlayer.Stop();
		BubbleCore::GetInst().ChangeLevel("RoundAEnterLevel");
		return;
	}

	//n초뒤에 다음 레벨로 전환
	AccTime += _DeltaTime;
	if (LevelChangeTime < AccTime)
	{
		SoundPlayer.Stop();
		BubbleCore::GetInst().ChangeLevel("RoundAEnterLevel");
	}
}

void EnterRoundLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	//다음 레벨로 전환되기 전에 거품과 플레이어를 지우기
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
	SoundPlayer.Stop();
}



