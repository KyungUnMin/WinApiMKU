#include "RoundA1Level.h"
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
#include "BubbleDestination.h"

const std::vector<float4> RoundA1Level::PlayerSpanwPos = 
{
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f }
};

const std::vector<std::vector<float4>> RoundA1Level::BubbleDestPos =
{
	{{100.f, 600.f},{100.f, 200.f},{860.f, 600.f},{860.f, 200.f},{480.f, 200.f}, {480.f, 100.f},{480.f, 600.f}, {480.f, 300.f}, {100.f, 400.f}, {860.f, 400.f}},

	{{350.f, 650.f},{100.f, 650},{100.f, 500.f},{100.f, 150.f},
		{610.f, 650}, {860.f, 650},{860.f, 500.f}, {860.f, 150.f},
			{480.f, 150.f}, {480.f, 250.f}, {480.f, 400.f}},

	{{650.f, 100.f},{350.f, 100.f},{100.f, 100.f},
		{100.f, 250.f},{350.f, 250.f},{650.f, 250.f},{860.f, 250.f},
			{860.f, 400.f},{650.f, 400.f},{350.f, 400.f},{100.f, 400.f},
				{100.f, 520.f},{350.f, 520.f},{650.f, 520.f},{860.f, 520.f},
					{860.f, 650.f},{650.f, 650.f},{350.f, 650.f},{100.f, 650.f},
												{350.f, 800.f},{650.f, 800.f}},

	{{100.f, 600.f},{100.f, 100.f},{480.f, 100.f}, {860.f, 100.f},{860.f, 600.f}},
	{{100.f, 600.f},{100.f, 100.f},{480.f, 100.f}, {860.f, 100.f},{860.f, 600.f}},
	{{100.f, 600.f},{100.f, 100.f},{480.f, 100.f}, {860.f, 100.f},{860.f, 600.f}},
};

RoundA1Level::RoundA1Level()
{

}

RoundA1Level::~RoundA1Level()
{

}

void RoundA1Level::Loading()
{
	//리소스 로드
	ResourceLoad();
	RoundLevelBase::LoadStage("A1", 6, 1);

	//뒤 배경과 레벨의 지형을 아래로 정렬하여 생성
	CreateBackGround();
	RoundLevelBase::CreateStage(float4::Down, RenderOrder::Obstacle1);

	//플레이어가 생성될 위치 설정
	SetPlayerSpawnPos(PlayerSpanwPos);

	CreateBubbleDest();
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
	Back->CreateRender("RoundA1_BackGround.bmp", RenderOrder::BackGround1);

	GameEngineRender* Effect = Back->CreateRender("RoundA1_BackEffect.bmp", RenderOrder::BackGround2);
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

void RoundA1Level::CreateBubbleDest()
{
	SetBubbleDest(BubbleDestPos);

	{
		size_t Stage = 0;
		ConnectDestToDest(Stage, 0, 1);
		ConnectDestToDest(Stage, 1, 4);
		ConnectDestToDest(Stage, 2, 3);
		ConnectDestToDest(Stage, 3, 4);
		ConnectDestToDest(Stage, 4, 5);
		ConnectDestToDest(Stage, 6, 7);
		ConnectDestToDest(Stage, 8, 1);
		ConnectDestToDest(Stage, 9, 3);
	}
	
	{
		size_t Stage = 1;
		ConnectDestToDest(Stage, 0, 1);
		ConnectDestToDest(Stage, 1, 3);
		ConnectDestToDest(Stage, 2, 3);
		ConnectDestToDest(Stage, 4, 5);
		ConnectDestToDest(Stage, 5, 7);
		ConnectDestToDest(Stage, 6, 7);
		ConnectDestToDest(Stage, 3, 8);
		ConnectDestToDest(Stage, 7, 8);
		ConnectDestToDest(Stage, 8, 9);
		ConnectDestToDest(Stage, 10, 9);
	}
	
	{
		size_t Stage = 2;
		for (size_t i = 0; i < 15; ++i)
		{
			ConnectDestToDest(Stage, i, i + 1);
		}

		ConnectDestToDest(Stage, 15, 16);
		ConnectDestToDest(Stage, 18, 17);
		ConnectDestToDest(Stage, 17, 19);
		ConnectDestToDest(Stage, 16, 20);
	}
	
}


void RoundA1Level::Update(float _DeltaTime)
{
	//RoundLevelBase::MoveToNextStage가 호출되었다면 Stage를 한칸 이동시킨다
	//만약 호출되지 않았다면 그때는 동작하지 않는다
	RoundLevelBase::Update(_DeltaTime);
	
	//치트키 눌렀는가?
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


