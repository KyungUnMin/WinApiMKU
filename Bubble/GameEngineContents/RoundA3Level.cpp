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
#include "BubbleDestHelper.h"

#include "MonsterSpawner.h"
#include "Monster_ZenChan.h"

RoundA3Level::RoundA3Level()
{

}

RoundA3Level::~RoundA3Level()
{

}

void RoundA3Level::Loading()
{
	RoundLevelBase::Loading();

	//리소스 로드
	ResourceLoad();
	RoundLevelBase::LoadStage("A3", 6, 1);

	//뒤 배경과 레벨의 지형을 오른쪽으로 정렬하여 생성
	CreateBackGround();
	RoundLevelBase::CreateStage(float4::Right, RenderOrder::Obstacle1);

	CreateBubbleDest();
	CreateMonsters();
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

void RoundA3Level::ChangeNextLevel()
{
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

void RoundA3Level::CreateBubbleDest()
{
	GetBubbleDestHelper()->SetBubbleDest(HelpLevelType::RoundA3);

	{
		size_t Stage = 0;
		for (size_t i = 0; i < 4; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i,i + 1);
		}
	}

	{
		size_t Stage = 1;
		for (size_t i = 0; i < 6; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i+1);
		}
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 6, 3);

		for (size_t i = 7; i < 10; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 10, 4);
		

		GetBubbleDestHelper()->ConnectDestToDest(Stage, 11, 6);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 12, 5);
	}

	{
		size_t Stage = 2;
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 0, 1);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 2, 3);

		for (size_t i = 4; i < 7; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 8; i < 11; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}
	}

	{
		size_t Stage = 3;
		for (size_t i = 0; i < 6; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 7; i < 13; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 14; i < 17; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}
	}

	{
		size_t Stage = 4;
		for (size_t i = 0; i < 9; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}
	}

	{
		size_t Stage = 5;
		for (size_t i = 0; i < 7; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 8; i < 13; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 14; i < 21; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

	}
}

void RoundA3Level::CreateMonsters()
{
	{
		MonsterSpawner* MonSpawner = GetMonsterSpawner(0);
		MonSpawner->ReserveSpanwer(4);

		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(165));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(291));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(278));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(409));
	}

	{
		MonsterSpawner* MonSpawner = GetMonsterSpawner(1);
		MonSpawner->ReserveSpanwer(6);

		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(367));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(369));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(495));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(497));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(591));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(593));
	}

	{
		MonsterSpawner* MonSpawner = GetMonsterSpawner(2);
		MonSpawner->ReserveSpanwer(4);

		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(259));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(295));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(390));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(410));
	}

	{
		MonsterSpawner* MonSpawner = GetMonsterSpawner(3);
		MonSpawner->ReserveSpanwer(7);

		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(176));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(238));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(242));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(298));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(310));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(451));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(477));
	}

	{
		MonsterSpawner* MonSpawner = GetMonsterSpawner(4);
		MonSpawner->ReserveSpanwer(5);

		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(157));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(245));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(337));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(458));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(518));
	}

	{
		MonsterSpawner* MonSpawner = GetMonsterSpawner(5);

		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(134));
	}
}

