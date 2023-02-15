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
#include "BubbleDestHelper.h"

#include "MonsterSpawner.h"
#include "Monster_ZenChan.h"


RoundA1Level::RoundA1Level()
{
	MonSpanwers[MonsterType::ZenChan] = new MonsterSpawner<Monster_ZenChan>(this);

}

RoundA1Level::~RoundA1Level()
{
	for (std::pair<MonsterType, MonsterSpawnerBase*> Pair : MonSpanwers)
	{
		if (nullptr == Pair.second)
			continue;

		delete Pair.second;
		Pair.second = nullptr;
	}

	MonSpanwers.clear();
}

void RoundA1Level::Loading()
{
	RoundLevelBase::Loading();

	//리소스 로드
	ResourceLoad();
	RoundLevelBase::LoadStage("A1", 6, 1);

	//뒤 배경과 레벨의 지형을 아래로 정렬하여 생성
	CreateBackGround();
	RoundLevelBase::CreateStage(float4::Down, RenderOrder::Obstacle1);

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
	GetBubbleDestHelper()->SetBubbleDest(HelpLevelType::RoundA1);

	{
		size_t Stage = 0;
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 0, 8);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 1, 4);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 2, 9);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 3, 4);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 4, 5);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 6, 7);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 8, 1);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 9, 3);
	}
	
	{
		size_t Stage = 1;
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 0, 1);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 1, 2);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 2, 3);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 4, 5);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 5, 6);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 6, 7);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 3, 8);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 7, 8);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 8, 9);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 10, 9);
	}
	
	{
		size_t Stage = 2;
		for (size_t i = 0; i < 15; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

		GetBubbleDestHelper()->ConnectDestToDest(Stage, 15, 16);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 18, 17);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 17, 19);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 16, 20);
	}
	
	{
		size_t Stage = 3;
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 0, 1);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 1, 2);

		GetBubbleDestHelper()->ConnectDestToDest(Stage, 3, 4);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 4, 5);

		for (size_t i = 6; i < 13; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

		GetBubbleDestHelper()->ConnectDestToDest(Stage, 13, 22);

		for (size_t i = 14; i < 23; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}
	}

	{
		size_t Stage = 4;

		for (size_t i = 0; i < 6; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}
		
		for (size_t i = 7; i < 13; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}
	}
}


void RoundA1Level::CreateMonster()
{

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


