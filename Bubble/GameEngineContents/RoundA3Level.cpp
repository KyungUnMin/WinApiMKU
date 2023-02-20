#include "RoundA3Level.h"
#include <vector>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineMath.h>
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
#include "Monster_Magician.h"
#include "Monster_HeitaKun.h"
#include "Monster_Monsta.h"
#include "Monster_Warurin.h"
#include "Monster_PuruPuru.h"

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
	const int StageCnt = 6;
	RoundLevelBase::LoadStage("A3", StageCnt, 1);
	StageBubbleSpawnCtrl.resize(StageCnt);

	//뒤 배경과 레벨의 지형을 오른쪽으로 정렬하여 생성
	CreateBackGround();
	RoundLevelBase::CreateStage(float4::Right, RenderOrder::Obstacle1);

	CreateBubbleDest();
	CreateMonsters();
	CreateStageBubbleSpawners();
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
	BubbleDestHelper* Helper = GetBubbleDestHelper();
	Helper->SetBubbleDest(HelpLevelType::RoundA3);

	{
		size_t Stage = 0;
		for (size_t i = 0; i < 4; ++i)
		{
			Helper->ConnectDestToDest(Stage, i,i + 1);
		}
	}

	{
		size_t Stage = 1;
		for (size_t i = 0; i < 6; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i+1);
		}
		Helper->ConnectDestToDest(Stage, 6, 3);

		for (size_t i = 7; i < 10; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}
		Helper->ConnectDestToDest(Stage, 10, 4);
		

		Helper ->ConnectDestToDest(Stage, 11, 6);
		Helper ->ConnectDestToDest(Stage, 12, 5);
	}

	{
		size_t Stage = 2;
		Helper ->ConnectDestToDest(Stage, 0, 1);
		Helper ->ConnectDestToDest(Stage, 2, 3);

		for (size_t i = 4; i < 7; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 8; i < 11; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}
	}

	{
		size_t Stage = 3;
		for (size_t i = 0; i < 6; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 7; i < 13; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 14; i < 17; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}
	}

	{
		size_t Stage = 4;
		for (size_t i = 0; i < 10; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}

		Helper->SetMoveDestPos(Stage, 10, { 0.f, -100.f });
	}

	{
		size_t Stage = 5;
		for (size_t i = 0; i < 7; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}
		Helper->SetMoveDestPos(Stage, 7, { 0.f, -100.f });


		for (size_t i = 8; i < 13; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}
		Helper->SetMoveDestPos(Stage, 13, { 0.f, -100.f });


		for (size_t i = 14; i < 21; ++i)
		{
			Helper->ConnectDestToDest(Stage, i, i + 1);
		}
		Helper->SetMoveDestPos(Stage, 21, { 0.f, -100.f });

	}
}

void RoundA3Level::CreateMonsters()
{
	{
		MonsterSpawner* MonSpawner = GetMonsterSpawner(0);
		MonSpawner->ReserveSpanwer(4);

		MonSpawner->CreateMonsters<Monster_HeitaKun>(BubbleDestHelper::GetGridPos(165));
		MonSpawner->CreateMonsters<Monster_HeitaKun>(BubbleDestHelper::GetGridPos(291));
		MonSpawner->CreateMonsters<Monster_HeitaKun>(BubbleDestHelper::GetGridPos(278));
		MonSpawner->CreateMonsters<Monster_HeitaKun>(BubbleDestHelper::GetGridPos(409));
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

		MonSpawner->CreateMonsters<Monster_Magician>(BubbleDestHelper::GetGridPos(259));
		MonSpawner->CreateMonsters<Monster_Magician>(BubbleDestHelper::GetGridPos(295));
		MonSpawner->CreateMonsters<Monster_Magician>(BubbleDestHelper::GetGridPos(390));
		MonSpawner->CreateMonsters<Monster_Magician>(BubbleDestHelper::GetGridPos(410));
	}

	{
		MonsterSpawner* MonSpawner = GetMonsterSpawner(3);
		MonSpawner->ReserveSpanwer(7);

		const float MonstaStartDegree = 70.f;
		const float4 MonstaStartDir = float4::AngleToDirection2DToDeg(MonstaStartDegree);

		MonSpawner->CreateMonsters<Monster_HeitaKun>(BubbleDestHelper::GetGridPos(176));

		GameEngineActor* Monsta = MonSpawner->CreateMonsters<Monster_Monsta>(BubbleDestHelper::GetGridPos(238));
		dynamic_cast<Monster_Monsta*>(Monsta)->Init({ MonstaStartDir.x, MonstaStartDir.y }, true);

		MonSpawner->CreateMonsters<Monster_Monsta>(BubbleDestHelper::GetGridPos(242));
		dynamic_cast<Monster_Monsta*>(Monsta)->Init({ -MonstaStartDir.x, MonstaStartDir.y }, false);

		MonSpawner->CreateMonsters<Monster_HeitaKun>(BubbleDestHelper::GetGridPos(298));
		MonSpawner->CreateMonsters<Monster_HeitaKun>(BubbleDestHelper::GetGridPos(310));
		MonSpawner->CreateMonsters<Monster_HeitaKun>(BubbleDestHelper::GetGridPos(451));
		MonSpawner->CreateMonsters<Monster_HeitaKun>(BubbleDestHelper::GetGridPos(477));
	}

	{
		MonsterSpawner* MonSpawner = GetMonsterSpawner(4);
		MonSpawner->ReserveSpanwer(5);

		MonSpawner->CreateMonsters<Monster_Warurin>(BubbleDestHelper::GetGridPos(157));
		MonSpawner->CreateMonsters<Monster_PuruPuru>(BubbleDestHelper::GetGridPos(245));
		MonSpawner->CreateMonsters<Monster_PuruPuru>(BubbleDestHelper::GetGridPos(337));
		MonSpawner->CreateMonsters<Monster_PuruPuru>(BubbleDestHelper::GetGridPos(458));
		MonSpawner->CreateMonsters<Monster_PuruPuru>(BubbleDestHelper::GetGridPos(518));
	}

	{
		MonsterSpawner* MonSpawner = GetMonsterSpawner(5);

		MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(134));
	}
}



void RoundA3Level::CreateStageBubbleSpawners()
{
	float4 TopPos[2] = { BubbleDestHelper::GetGridPos(10), BubbleDestHelper::GetGridPos(21) };
	float4 BottomPos[2] = { BubbleDestHelper::GetGridPos(747), BubbleDestHelper::GetGridPos(758) };

	//Stage1
	{
		const int StageNum = 1;
		BubbleSpawner* Spawner = nullptr;
		const float FireFixedTime = 3.f;

		for (size_t i = 0; i < 2; ++i)
		{
			Spawner = CreateActor<BubbleSpawner>();
			Spawner->SetPos(TopPos[i]);
			StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner, static_cast<BubbleColor>(i)));

			Spawner = CreateActor<BubbleSpawner>();
			Spawner->SetPos(TopPos[i]);
			StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner, static_cast<BubbleColor>(i), FireFixedTime, FireFixedTime));
			Spawner->SetBubbleType(BubbleMissleType::Fire);
		}

		for (size_t i = 0; i < 2; ++i)
		{
			Spawner = CreateActor<BubbleSpawner>();
			Spawner->SetPos(BottomPos[i]);
			StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner, static_cast<BubbleColor>(i + 2)));

			Spawner = CreateActor<BubbleSpawner>();
			Spawner->SetPos(BottomPos[i]);
			StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner, static_cast<BubbleColor>(i + 2), FireFixedTime, FireFixedTime));
			Spawner->SetBubbleType(BubbleMissleType::Fire);
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

		for (size_t i = 0; i < 2; ++i)
		{
			Spawner = CreateActor<BubbleSpawner>();
			Spawner->SetPos(BottomPos[i]);
			StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner, static_cast<BubbleColor>(i + 2)));
		}
	}

	//Stage3
	{
		const int StageNum = 3;
		BubbleSpawner* Spawner = nullptr;
		const float WaveFixedTime = 3.f;
		
		Spawner = CreateActor<BubbleSpawner>();
		Spawner->SetPos(BottomPos[0]);
		StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner, BubbleColor::Yellow));

		Spawner = CreateActor<BubbleSpawner>();
		Spawner->SetPos(BottomPos[0]);
		StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner, BubbleColor::Yellow, WaveFixedTime, WaveFixedTime));
		Spawner->SetBubbleType(BubbleMissleType::Water);



		Spawner = CreateActor<BubbleSpawner>();
		Spawner->SetPos(BottomPos[1]);
		StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner, BubbleColor::Pink));

		Spawner = CreateActor<BubbleSpawner>();
		Spawner->SetPos(BottomPos[1]);
		StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner, BubbleColor::Pink, WaveFixedTime, WaveFixedTime));
		Spawner->SetBubbleType(BubbleMissleType::Water);
	}

	//Stage4
	{
		const int StageNum = 4;
		BubbleSpawner* Spawner = nullptr;
		const float WindyFixedTime = 3.f;

		Spawner = CreateActor<BubbleSpawner>();
		Spawner->SetPos(TopPos[1]);
		StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner, BubbleColor::Blue));

		Spawner = CreateActor<BubbleSpawner>();
		Spawner->SetPos(TopPos[1]);
		StageBubbleSpawnCtrl[StageNum].push_back(StageBubbleSpawnerInfo(Spawner, BubbleColor::Blue, WindyFixedTime, WindyFixedTime));
		Spawner->SetBubbleType(BubbleMissleType::Windy);
	}

}










void RoundA3Level::Update(float _DeltaTime)
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


void RoundA3Level::Update_StageBubbleSpawner(float _DeltaTime)
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


void RoundA3Level::ChangeNextLevel()
{
	//다음레벨로 전환
	BubbleCore::GetInst().ChangeLevel("EndingLevel");
}