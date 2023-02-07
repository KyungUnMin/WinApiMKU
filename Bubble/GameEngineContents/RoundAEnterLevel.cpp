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

#include "BubbleDestination.h"

#include "MonsterBase.h"

const std::vector<float4>						RoundAEnterLevel::PlayerSpanwPos = { { 100.f, 700.f } };
const float4											RoundAEnterLevel::MonsterSpawnPos[3] =
{
	{400.f, 430.f},{500.f, 430.f},{600.f, 430.f}
};

const std::vector<std::vector<float4>>	RoundAEnterLevel::BubbleDestPos =
{
	{{100.f, 100.f},{250.f, 100.f}, {480.f, 100.f}, {710.f, 100.f} ,{860.f, 100.f}}
};


RoundAEnterLevel::RoundAEnterLevel()
{

}

RoundAEnterLevel::~RoundAEnterLevel()
{

}


void RoundAEnterLevel::Loading()
{
	//���ҽ� �ε�
	ResourceLoad();
	RoundLevelBase::LoadStage("AEnter", 1, 1);

	//�� ���� ������ ���� ����
	CreateBackGround();
	RoundLevelBase::CreateStage(float4::Right, RenderOrder::Obstacle1);

	//�÷��̾ ������ ��ġ ����
	SetPlayerSpawnPos(PlayerSpanwPos);

	//���� �¿�� �����̴� �ϴ� ����
	CreateActor<RoundA_Enter_Sky>();
	//���� ������ �Ѿ�� �� ����
	CreateDoor();

	Monsters.reserve(3);
	for (size_t i = 0; i < 3; ++i)
	{
		MonsterBase* Monster = CreateActor<MonsterBase>();
		Monster->SetPos(MonsterSpawnPos[i]);
		Monsters.push_back(Monster);
	}

	CreateBubbleDest();
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
	const float4 ScreenSize = GameEngineWindow::GetScreenSize();
	const float4 Pivot = float4{ ScreenSize.x * 0.5f, ScreenSize.y * 0.7f };
	const float4 Offset[3] = { {-150.f, 0.f} , {0.f,0.f}, {150.f, 0.f} };
	for (size_t i = 0; i < 3; ++i)
	{
		Door[i] = CreateActor<NextDoor>();
		Door[i]->SelectDoor(DoorType::Blue, { 200.f, 200.f }, RenderOrder::Door);
		Door[i]->SetPos(Pivot + Offset[i]);
		Door[i]->Off();
	}
}

void RoundAEnterLevel::CreateBubbleDest()
{
	SetBubbleDest(BubbleDestPos);

	size_t Stage = 0;
	ConnectDestToDest(Stage, 0, 2);
	ConnectDestToDest(Stage, 1, 2);
	ConnectDestToDest(Stage, 3, 2);
	ConnectDestToDest(Stage, 4, 2);
}

void RoundAEnterLevel::Update(float _DeltaTime)
{
	for (size_t i = 0; i < Monsters.size(); ++i)
	{
		if (Monsters[i]->IsUpdate())
			return;
	}

	for (size_t i = 0; i < 3; ++i)
	{
		Door[i]->On();
	}


	//���� ���õǾ������� Ȯ��
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
	
	//�ش� ���� ���� �ִϸ��̼��� �۵���Ű�� NextLevelTime �ð���ŭ ���
	NextLevelTime -= _DeltaTime;
	if (0 < NextLevelTime)
		return;

	//������ ���� ���� ���� ��ȯ
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

	for (size_t i = 0; i < 3; ++i)
	{
		Door[i]->Off();
	}
}


void RoundAEnterLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	RoundLevelBase::LevelChangeEnd(_NextLevel);

	//���� �ִϸ��̼ǵ��� �ʱ�ȭ
	for (size_t i = 0; i < 3; ++i)
	{
		Door[i]->Reset();
	}

	for (size_t i = 0; i < Monsters.size(); ++i)
	{
		Monsters[i]->On();
		Monsters[i]->Reset();
		Monsters[i]->SetPos(MonsterSpawnPos[i]);
	}

	//���� ���� �ʱ�ȭ
	SelectedDoor = -1;
	NextLevelTime = 3.f;
}
