#include "RoundA2Level.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "BubbleCore.h"
#include "BackGround.h"
#include "ContentsEnum.h"
#include "ContentsDefine.h"
#include "PlayerBase.h"


const std::vector<float4> RoundA2Level::PlayerSpanwPos = 
{
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f }
};

RoundA2Level::RoundA2Level()
{

}

RoundA2Level::~RoundA2Level()
{

}



void RoundA2Level::Loading()
{
	//리소스 로드
	ResourceLoad();
	RoundLevelBase::LoadStage("A2", 6, 1);

	//배경 및 레벨의 지형을 오른쪽으로 정렬하여 생성
	CreateBackGround();
	RoundLevelBase::CreateStage(float4::Right, RenderOrder::Obstacle1);

	//플레이어가 생성될 위치 설정
	SetPlayerSpawnPos(PlayerSpanwPos);
}


void RoundA2Level::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("RoundRooms");
	Dir.Move("RoundA");
	Dir.Move("RoundA2");

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RoundA2_BackGround1.bmp"))->Cut(4, 2);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RoundA2_BackGround2.bmp"))->Cut(2, 1);
}

//2개의 배경 애니메이션
void RoundA2Level::CreateBackGround()
{
	BackGround* Back = CreateActor<BackGround>();
	GameEngineRender* Render1 = Back->CreateRender("RoundA2_BackGround1.bmp", RenderOrder::BackGround1);
	Render1->CreateAnimation
	({
		.AnimationName = "Idle",
		.ImageName = "RoundA2_BackGround1.bmp",
		.Start = 0,
		.End = 6,
		.InterTimer = 0.15f,
	});
	Render1->ChangeAnimation("Idle");

	GameEngineRender* Render2 = Back->CreateRender("RoundA2_BackGround2.bmp", RenderOrder::BackGround2);
	Render2->CreateAnimation
	({
		.AnimationName = "Idle",
		.ImageName = "RoundA2_BackGround2.bmp",
		.Start = 0,
		.End = 1,
		.InterTimer = 0.25f,
	});
	Render2->ChangeAnimation("Idle");
}


void RoundA2Level::Update(float _DeltaTime)
{
	//RoundLevelBase::MoveToNextStage가 호출되었다면 Stage를 한칸 이동시킨다
	//만약 호출되지 않았다면 그때는 동작하지 않는다
	RoundLevelBase::Update(_DeltaTime);

	//치트키를 눌렀는가?
	if (false == GameEngineInput::IsDown(CHEET_STAGE_CLEAR))
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


