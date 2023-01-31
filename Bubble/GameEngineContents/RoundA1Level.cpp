#include "RoundA1Level.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "BubbleCore.h"
#include "BackGround.h"
#include "ContentsEnum.h"
#include "PlayerBase.h"


RoundA1Level::RoundA1Level()
{

}

RoundA1Level::~RoundA1Level()
{

}

void RoundA1Level::Loading()
{
	//플레이어가 생성될 위치 설정
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	SetPlayerSpawnPos({ ScreenSize.x * 0.2f,  ScreenSize.y * 0.8f });

	//리소스 로드
	ResourceLoad();
	RoundLevelBase::LoadObstacle("A1", 6, 1);

	//뒤 배경과 레벨의 지형을 아래로 정렬하여 생성
	CreateBackGround();
	RoundLevelBase::CreateObstacle(float4::Down, RoundRenderOrder::Obstacle1);

	//임시적인 치트키
	GameEngineInput::CreateKey("A1_NextStage", VK_F1);
}

void RoundA1Level::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("RoundRooms");
	Dir.Move("RoundA");
	Dir.Move("RoundA1");

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RoundA1_BackGround.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RoundA1_BackEffect.bmp"))->Cut(3, 1);
}


//2개의 배경 애니메이션 생성
void RoundA1Level::CreateBackGround()
{
	BackGround* Back = CreateActor<BackGround>();
	Back->RenderReserve(2);
	Back->CreateRender("RoundA1_BackGround.bmp", RoundRenderOrder::BackGround1);

	GameEngineRender* Effect = Back->CreateRender("RoundA1_BackEffect.bmp", RoundRenderOrder::BackGround2);
	Effect->CreateAnimation
	({
		.AnimationName = "Idle",
		.ImageName = "RoundA1_BackEffect.bmp",
		.Start = 0,
		.End = 2,
		.InterTimer = 0.15f
	});

	Effect->ChangeAnimation("Idle");
}


void RoundA1Level::Update(float _DeltaTime)
{
	//RoundLevelBase::MoveToNextStage가 호출되었다면 Stage를 한칸 이동시킨다
	//만약 호출되지 않았다면 그때는 동작하지 않는다
	RoundLevelBase::Update(_DeltaTime);
	
	//치트키 눌렀는가?
	if (false == GameEngineInput::IsDown("A1_NextStage"))
		return;

	//다음으로 이동중인가?
	if (true == RoundLevelBase::MoveToNextStage())
		return;

	//이 Stage가 이번 Round의 마지막 Stage인가?
	if (false == RoundLevelBase::IsLastStage())
		return;

	//다음레벨로 전환
	BubbleCore::GetInst().ChangeLevel("EndingLevel");
}


//이 레벨이 시작되었을때
void RoundA1Level::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	//플레이어 생성
	RoundLevelBase::LevelChangeStart(_PrevLevel);
	GetPlayer()->SetPos(GetPlayerSpawnPos());
}

