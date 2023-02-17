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
#include "BubbleSpawner.h"

#include "MonsterSpawner.h"
#include "Monster_ZenChan.h"
#include "Monster_PHLoop.h"


RoundA1Level::RoundA1Level()
{
	
}

RoundA1Level::~RoundA1Level()
{
	
}

void RoundA1Level::Loading()
{
	RoundLevelBase::Loading();

	//리소스 로드
	ResourceLoad();
	const int StageCnt = 6;
	RoundLevelBase::LoadStage("A1", StageCnt, 1);
	StageBubbleSpawnCtrl.resize(StageCnt);

	//뒤 배경과 레벨의 지형을 아래로 정렬하여 생성
	CreateBackGround();
	RoundLevelBase::CreateStage(float4::Down, RenderOrder::Obstacle1);

	CreateBubbleDest();
	CreateMonsters();
	CreateStageBubbleSpawners();
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


void RoundA1Level::CreateMonsters()
{
	{
		MonsterSpawner* MonSpawner = GetMonsterSpawner(0);
		MonSpawner->ReserveSpanwer(4);
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(269));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(275));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(395));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(405));
	}
	
	{
		MonsterSpawner* MonSpawner = GetMonsterSpawner(1);
		MonSpawner->ReserveSpanwer(4);
		MonSpawner->CreateMonsters<Monster_PHLoop>(BubbleDestHelper::GetGridPos(263));
		MonSpawner->CreateMonsters<Monster_PHLoop>(BubbleDestHelper::GetGridPos(280));
		MonSpawner->CreateMonsters<Monster_PHLoop>(BubbleDestHelper::GetGridPos(427));
		MonSpawner->CreateMonsters<Monster_PHLoop>(BubbleDestHelper::GetGridPos(436));
	}

	{
		MonsterSpawner* MonSpawner = GetMonsterSpawner(2);
		MonSpawner->ReserveSpanwer(6);
		MonSpawner->CreateMonsters<Monster_PHLoop>(BubbleDestHelper::GetGridPos(153));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(141));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(259));
		MonSpawner->CreateMonsters<Monster_PHLoop>(BubbleDestHelper::GetGridPos(279));
		MonSpawner->CreateMonsters<Monster_PHLoop>(BubbleDestHelper::GetGridPos(433));
		MonSpawner->CreateMonsters<Monster_PHLoop>(BubbleDestHelper::GetGridPos(455));
	}

	{
		MonsterSpawner* MonSpawner = GetMonsterSpawner(3);
		MonSpawner->ReserveSpanwer(6);

		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(131));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(262));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(424));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(156));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(282));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(439));
	}

	{
		MonsterSpawner* MonSpawner = GetMonsterSpawner(4);
		MonSpawner->ReserveSpanwer(8);

		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(134));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(154));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(368));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(427));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(489));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(437));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(503));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(656));
	}

	{
		MonsterSpawner* MonSpawner = GetMonsterSpawner(5);

		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(134));
	}
}





void RoundA1Level::CreateStageBubbleSpawners()
{
	float4 TopPos[2] = { BubbleDestHelper::GetGridPos(10), BubbleDestHelper::GetGridPos(21) };
	float4 BottomPos[2] = { BubbleDestHelper::GetGridPos(747), BubbleDestHelper::GetGridPos(758) };

	//Stage0
	{
		const int StageNum = 0;
		BubbleSpawner* Spawner = nullptr;

		for (size_t i = 0; i < 2; ++i)
		{
			Spawner = CreateActor<BubbleSpawner>();
			Spawner->SetPos(TopPos[i]);
			StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner));
		}
	}

	//Stage1
	{
		const int StageNum = 1;
		BubbleSpawner* Spawner = nullptr;

		for (size_t i = 0; i < 2; ++i)
		{
			Spawner = CreateActor<BubbleSpawner>();
			Spawner->SetPos(BottomPos[i]);
			StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner));
		}
	}

	//Stage2
	{
		const int StageNum = 2;
		BubbleSpawner* Spawner = nullptr;

		for (size_t i = 0; i < 2; ++i)
		{
			Spawner = CreateActor<BubbleSpawner>();
			Spawner->SetPos(TopPos[i]);
			StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner));
		}

		const float WaveFixedTime = 3.f;
		for (size_t i = 0; i < 2; ++i)
		{
			Spawner = CreateActor<BubbleSpawner>();
			Spawner->SetPos(TopPos[i]);
			StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner, BubbleColor::Blue,WaveFixedTime, WaveFixedTime));
			Spawner->SetBubbleType(BubbleMissleType::Water);
			Spawner->SetColor(BubbleColor::Blue);
		}
	}

	//Stage3
	{
		const int StageNum = 3;
		BubbleSpawner* Spawner = nullptr;

		for (size_t i = 0; i < 2; ++i)
		{
			Spawner = CreateActor<BubbleSpawner>();
			Spawner->SetPos(TopPos[i]);
			StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner));
		}
	}

	//Stage4
	{
		const int StageNum = 4;
		BubbleSpawner* Spawner = nullptr;

		for (size_t i = 0; i < 2; ++i)
		{
			Spawner = CreateActor<BubbleSpawner>();
			Spawner->SetPos(BottomPos[i]);
			StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner));
		}

		const float ElecFixedTime = 3.f;
		for (size_t i = 0; i < 2; ++i)
		{
			Spawner = CreateActor<BubbleSpawner>();
			Spawner->SetPos(BottomPos[i]);
			StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner, BubbleColor::Yellow,ElecFixedTime, ElecFixedTime));
			Spawner->SetBubbleType(BubbleMissleType::Electronic);
			Spawner->SetColor(BubbleColor::Yellow);
		}
	}


}








void RoundA1Level::Update(float _DeltaTime)
{
	Update_StageBubbleSpawner(_DeltaTime);

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



void RoundA1Level::Update_StageBubbleSpawner(float _DeltaTime)
{
	size_t NowStage = GetNowStage();

	//현재 스테이지에는 버블스포너가 없음
	if (true == StageBubbleSpawnCtrl[NowStage].empty())
		return;

	static const float LowDuration = 0.5f;
	static const float HighDuration = 3.f;
	std::vector<StageBubbleSpawnerInfo>& NowStageBubbleSpawners = StageBubbleSpawnCtrl[NowStage];
	for (size_t i = 0; i < NowStageBubbleSpawners.size(); ++i)
	{
		StageBubbleSpawnerInfo& Info = NowStageBubbleSpawners[i];
		Info.BubbleCreate(_DeltaTime);
	}
}







void RoundA1Level::ChangeNextLevel()
{
	//다음레벨로 전환
	BubbleCore::GetInst().ChangeLevel("EndingLevel");
}



