#include "RoundAEnterLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineResources.h>
#include "BubbleCore.h"
#include "ContentsEnum.h"
#include "BackGround.h"
#include "RoundA_Enter_Sky.h"
#include "NextDoor.h"
#include "PlayerBase.h"
#include "BubbleDestHelper.h"
#include "Monster_ZenChan.h"
#include "MonsterSpawner.h"

RoundAEnterLevel::RoundAEnterLevel()
{
}

RoundAEnterLevel::~RoundAEnterLevel()
{
	
}



void RoundAEnterLevel::Loading()
{
	RoundLevelBase::Loading();

	//리소스 로드
	ResourceLoad();
	RoundLevelBase::LoadStage("AEnter", 1, 1);

	//뒤 배경과 레벨의 지형 생성
	CreateBackGround();
	RoundLevelBase::CreateStage(float4::Right, RenderOrder::Obstacle1);

	//뒤쪽 좌우로 움직이는 하늘 생성
	CreateActor<RoundA_Enter_Sky>();
	//다음 레벨로 넘어가는 문 생성
	CreateDoor();

	CreateBubbleDest();

	CreateMonsters();
}

void RoundAEnterLevel::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("RoundRooms");
	Dir.Move("RoundA");
	Dir.Move("RoundAEnter");

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RoundA_Enter_Sky.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RoundA_Enter_BackGround.bmp"));
}

void RoundAEnterLevel::CreateBackGround()
{
	BackGround* Back = CreateActor<BackGround>();
	Back->CreateRender("RoundA_Enter_BackGround.bmp", RenderOrder::BackGround2);
}

void RoundAEnterLevel::CreateDoor()
{
	//620, 624, 628
	float4 Pos[3];
	float4 Offset = float4{ 0.f, -5.f };
	Pos[0] = GetBubbleDestHelper()->GetPointPos(619, Offset);
	Pos[1] = GetBubbleDestHelper()->GetPointPos(624, Offset);
	Pos[2] = GetBubbleDestHelper()->GetPointPos(629, Offset);

	for (size_t i = 0; i < 3; ++i)
	{
		Door[i] = CreateActor<NextDoor>();
		Door[i]->SelectDoor(DoorType::Blue, { 400.f, 400.f }, RenderOrder::Door);
		Door[i]->SetPos(Pos[i]);
		Door[i]->Off();
	}
}

void RoundAEnterLevel::CreateBubbleDest()
{
	GetBubbleDestHelper()->SetBubbleDest(HelpLevelType::RoundAEnter);

	size_t Stage = 0;
	GetBubbleDestHelper()->ConnectDestToDest(Stage, 0, 1);
	GetBubbleDestHelper()->ConnectDestToDest(Stage, 1, 2);
	GetBubbleDestHelper()->ConnectDestToDest(Stage, 3, 2);
	GetBubbleDestHelper()->ConnectDestToDest(Stage, 4, 3);
}

void RoundAEnterLevel::CreateMonsters()
{
	MonSpawner = GetMonsterSpawner(0);
	MonSpawner->ReserveSpanwer(3);
	MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(236));
	MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(240));
	MonSpawner->CreateMonsters<Monster_ZenChan>(BubbleDestHelper::GetGridPos(244));
}









void RoundAEnterLevel::Update(float _DeltaTime)
{
	if (false == MonSpawner->IsAllMonsterOff())
		return;

	for (size_t i = 0; i < 3; ++i)
	{
		Door[i]->On();
	}

	//문이 선택되었을때를 확인
	if (SelectedDoor < 0)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			if (false == Door[i]->IsOpened())
				continue;

			SelectedDoor = static_cast<int>(i);
		}

		return;
	}
	
	//해당 문을 여는 애니메이션을 작동시키고 NextLevelTime 시간만큼 대기
	NextLevelTime -= _DeltaTime;
	if (0 < NextLevelTime)
		return;

	//선택한 문에 따라서 레벨 전환
	if (0 == SelectedDoor)
	{
		BubbleCore::GetInst().ChangeLevel("RoundA1Level");
	}
	else if (1 == SelectedDoor)
	{
		BubbleCore::GetInst().ChangeLevel("RoundA2Level");
	}
	else
	{
		BubbleCore::GetInst().ChangeLevel("RoundA3Level");
	}
}

void RoundAEnterLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	RoundLevelBase::LevelChangeStart(_PrevLevel);
	MonSpawner->AllMonsterOn();

	for (size_t i = 0; i < 3; ++i)
	{
		Door[i]->Off();
	}
}


void RoundAEnterLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	RoundLevelBase::LevelChangeEnd(_NextLevel);

	//문의 애니메이션들을 초기화
	for (size_t i = 0; i < 3; ++i)
	{
		Door[i]->Reset();
	}

	//문의 선택 초기화
	SelectedDoor = -1;
	NextLevelTime = 3.f;
}
