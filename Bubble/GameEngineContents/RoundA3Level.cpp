#include "RoundA3Level.h"
#include <vector>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "BubbleCore.h"
#include "BackGround.h"
#include "ContentsEnum.h"
#include "ContentsDefine.h"
#include "PlayerBase.h"

const std::vector<float4> RoundA3Level::PlayerSpanwPos = 
{
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f }
};

RoundA3Level::RoundA3Level()
{

}

RoundA3Level::~RoundA3Level()
{

}

void RoundA3Level::Loading()
{
	//리소스 로드
	ResourceLoad();
	RoundLevelBase::LoadStage("A3", 6, 1);

	//뒤 배경과 레벨의 지형을 오른쪽으로 정렬하여 생성
	CreateBackGround();
	RoundLevelBase::CreateStage(float4::Right, RenderOrder::Obstacle1);

	//플레이어가 생성될 위치 설정
	SetPlayerSpawnPos(PlayerSpanwPos);
}



void RoundA3Level::Update(float _DeltaTime)
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





void RoundA3Level::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("RoundRooms");
	Dir.Move("RoundA");
	Dir.Move("RoundA3");

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RoundA3_BackGround1.bmp"))->Cut(5, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RoundA3_BackGround2.bmp"))->Cut(3, 1);
}


//2개의 배경 애니메이션
void RoundA3Level::CreateBackGround()
{
	BackGround* Back = CreateActor<BackGround>();
	Back->RenderReserve(2);

	GameEngineRender* Render1 = Back->CreateRender("RoundA3_BackGround1.bmp", RenderOrder::BackGround1);

	Render1->CreateAnimation
	({
		.AnimationName = "Idle",
		.ImageName = "RoundA3_BackGround1.bmp",
		.InterTimer = 0.2f,
		.FrameIndex = std::vector<int> { 0, 1, 2, 3, 4, 3 },
	});
	Render1->ChangeAnimation("Idle");

	GameEngineRender* Render2 = Back->CreateRender("RoundA3_BackGround2.bmp", RenderOrder::BackGround2);
	Render2->CreateAnimation
	({
		.AnimationName = "Idle",
		.ImageName = "RoundA3_BackGround2.bmp",
		.InterTimer = 0.2f,
		.FrameIndex = std::vector<int> { 0, 1, 2, 1 }
	});
	Render2->ChangeAnimation("Idle");
}

