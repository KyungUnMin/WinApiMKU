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
#include "BubbleDestHelper.h"
#include "BubbleSpawner.h"

#include "MonsterSpawner.h"
#include "Monster_ZenChan.h"
#include "Monster_MightA.h"
#include "Monster_Myata.h"
#include "Monster_Dorabo.h"
#include "Monster_Magician.h"
#include "Monster_Warurin.h"

RoundA2Level::RoundA2Level()
{

}

RoundA2Level::~RoundA2Level()
{

}



void RoundA2Level::Loading()
{
	RoundLevelBase::Loading();

	//리소스 로드
	ResourceLoad();
	const int StageCnt = 6;
	RoundLevelBase::LoadStage("A2", StageCnt, 1);
	StageBubbleSpawnCtrl.resize(StageCnt);

	//배경 및 레벨의 지형을 오른쪽으로 정렬하여 생성
	CreateBackGround();
	RoundLevelBase::CreateStage(float4::Right, RenderOrder::Obstacle1);


	CreateBubbleDest();
	CreateMonsters();
	CreateStageBubbleSpawners();
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

void RoundA2Level::CreateBubbleDest()
{
	BubbleDestHelper* Helper = GetBubbleDestHelper();
	Helper->SetBubbleDest(HelpLevelType::RoundA2);

	{
		size_t Stage = 0;
		for (size_t i = 0; i < 2; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}
		
		for (size_t i = 3; i < 5; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}
	}

	{
		size_t Stage = 1;
		for (size_t i = 0; i < 5; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 6; i < 11; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 12; i < 15; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}

	}

	{
		size_t Stage = 2;
		for (size_t i = 0; i < 7; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 8; i < 15; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}

	}

	{
		size_t Stage = 3;
		for (size_t i = 0; i < 4; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 5; i < 9; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}

		Helper->ConnectDestToDest(Stage, 10, 1);
		Helper->ConnectDestToDest(Stage, 11, 6);
		Helper->ConnectDestToDest(Stage, 12, 3);
		Helper->ConnectDestToDest(Stage, 13, 8);
	}

	{
		size_t Stage = 4;
		for (size_t i = 0; i < 5; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 6; i < 11; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 12; i < 15; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}
	}

	{
		size_t Stage = 5;
		for (size_t i = 0; i < 11; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 12; i < 14; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}
		Helper->ConnectDestToDest(Stage, 14, 4);

		for (size_t i = 15; i < 17; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}
		Helper->ConnectDestToDest(Stage, 17, 5);

		for (size_t i = 18; i < 20; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}
		Helper->ConnectDestToDest(Stage, 20, 6);

		Helper->SetMoveDestPos(Stage, 11, { 0.f, -100.f });
	}

}

void RoundA2Level::CreateMonsters()
{
	{
		MonsterSpawner* MonSpawner = GetMonsterSpawner(0);
		MonSpawner->ReserveSpanwer(4);

		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(234));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(246));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(359));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(377));
	}

	{
		MonsterSpawner* MonSpawner = GetMonsterSpawner(1);
		MonSpawner->ReserveSpanwer(4);

		MonSpawner->CreateMonsters<Monster_MightA>(BubbleDestHelper::GetGridPos(184));
		MonSpawner->CreateMonsters<Monster_Myata>(BubbleDestHelper::GetGridPos(308));
		MonSpawner->CreateMonsters<Monster_Myata>(BubbleDestHelper::GetGridPos(465));
		MonSpawner->CreateMonsters<Monster_Myata>(BubbleDestHelper::GetGridPos(588));
	}

	{
		MonsterSpawner* MonSpawner = GetMonsterSpawner(2);
		MonSpawner->ReserveSpanwer(4);

		MonSpawner->CreateMonsters<Monster_MightA>(BubbleDestHelper::GetGridPos(233));
		MonSpawner->CreateMonsters<Monster_MightA>(BubbleDestHelper::GetGridPos(247));
		MonSpawner->CreateMonsters<Monster_Myata>(BubbleDestHelper::GetGridPos(359));
		MonSpawner->CreateMonsters<Monster_Myata>(BubbleDestHelper::GetGridPos(377));
	}

	{
		MonsterSpawner* MonSpawner = GetMonsterSpawner(3);
		MonSpawner->ReserveSpanwer(6);

		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(330));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(342));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(426));
		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(438));
		MonSpawner->CreateMonsters<Monster_Magician>(BubbleDestHelper::GetGridPos(589));
		MonSpawner->CreateMonsters<Monster_Magician>(BubbleDestHelper::GetGridPos(595));
	}

	{
		MonsterSpawner* MonSpawner = GetMonsterSpawner(4);
		MonSpawner->ReserveSpanwer(7);

		MonSpawner->CreateMonsters<Monster_Myata>(BubbleDestHelper::GetGridPos(173));
		MonSpawner->CreateMonsters<Monster_Myata>(BubbleDestHelper::GetGridPos(179));
		MonSpawner->CreateMonsters<Monster_Dorabo>(BubbleDestHelper::GetGridPos(262));
		MonSpawner->CreateMonsters<Monster_Dorabo>(BubbleDestHelper::GetGridPos(264));
		MonSpawner->CreateMonsters<Monster_Dorabo>(BubbleDestHelper::GetGridPos(280));
		MonSpawner->CreateMonsters<Monster_Dorabo>(BubbleDestHelper::GetGridPos(282));
		MonSpawner->CreateMonsters<Monster_Warurin>(BubbleDestHelper::GetGridPos(624));
	}

	{
		MonsterSpawner* MonSpawner = GetMonsterSpawner(5);

		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(134));
	}
}

void RoundA2Level::CreateStageBubbleSpawners()
{
	float4 TopPos[2] = { BubbleDestHelper::GetGridPos(10), BubbleDestHelper::GetGridPos(21) };
	float4 BottomPos[2] = { BubbleDestHelper::GetGridPos(747), BubbleDestHelper::GetGridPos(758) };

	//Stage1
	{
		const int StageNum = 1;
		BubbleSpawner* Spawner = nullptr;

		for (size_t i = 0; i < 2; ++i)
		{
			Spawner = CreateActor<BubbleSpawner>();
			Spawner->SetPos(TopPos[i]);
			StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner, static_cast<BubbleColor>(i)));
		}

		for (size_t i = 0; i < 2; ++i)
		{
			Spawner = CreateActor<BubbleSpawner>();
			Spawner->SetPos(TopPos[i]);
			StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner, static_cast<BubbleColor>(i)));
			Spawner->SetBubbleType(BubbleMissleType::Water);
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
			StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner, static_cast<BubbleColor>(i)));
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
			StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner, static_cast<BubbleColor>(i)));
		}

		for (size_t i = 0; i < 2; ++i)
		{
			Spawner = CreateActor<BubbleSpawner>();
			Spawner->SetPos(BottomPos[i]);
			StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner, static_cast<BubbleColor>(i + 2)));
		}

		const float ElecFixedTime = 3.f;
		for (size_t i = 0; i < 2; ++i)
		{
			Spawner = CreateActor<BubbleSpawner>();
			Spawner->SetPos(TopPos[i]);
			StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner, static_cast<BubbleColor>(i),ElecFixedTime, ElecFixedTime));
			Spawner->SetBubbleType(BubbleMissleType::Electronic);
		}

		for (size_t i = 0; i < 2; ++i)
		{
			Spawner = CreateActor<BubbleSpawner>();
			Spawner->SetPos(BottomPos[i]);
			StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner, static_cast<BubbleColor>(i + 2),ElecFixedTime, ElecFixedTime));
			Spawner->SetBubbleType(BubbleMissleType::Electronic);
		}
	}

	//Stage4
	{
		const int StageNum = 4;
		BubbleSpawner* Spawner = nullptr;
		float4 Stage4Pos[2] = { BubbleDestHelper::GetGridPos(8), BubbleDestHelper::GetGridPos(19) };

		for (size_t i = 0; i < 2; ++i)
		{
			Spawner = CreateActor<BubbleSpawner>();
			Spawner->SetPos(Stage4Pos[i]);
			StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner, static_cast<BubbleColor>(i)));
		}

		const float RainBowFixedTime = 3.f;
		for (size_t i = 0; i < 2; ++i)
		{
			Spawner = CreateActor<BubbleSpawner>();
			Spawner->SetPos(Stage4Pos[i]);
			StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner, static_cast<BubbleColor>(i),RainBowFixedTime, RainBowFixedTime));
			Spawner->SetBubbleType(BubbleMissleType::Rainbow);
		}
	}
}




void RoundA2Level::Update(float _DeltaTime)
{
	Update_StageBubbleSpawner(_DeltaTime);

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

void RoundA2Level::Update_StageBubbleSpawner(float _DeltaTime)
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


void RoundA2Level::ChangeNextLevel()
{
	//다음레벨로 전환
	BubbleCore::GetInst().ChangeLevel("EndingLevel");
}


