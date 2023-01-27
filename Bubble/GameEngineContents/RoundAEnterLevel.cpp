#include "RoundAEnterLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include "BubbleCore.h"
#include "ContentsEnum.h"
#include "BackGround.h"
#include "RoundA_Enter_Sky.h"
#include "NextDoor.h"
#include "PlayerBase.h"

RoundAEnterLevel::RoundAEnterLevel()
{

}

RoundAEnterLevel::~RoundAEnterLevel()
{

}


void RoundAEnterLevel::Loading()
{
	ResourceLoad();
	RoundLevelBase::LoadObstacle("AEnter", 1, 1);

	CreateBackGround();
	RoundLevelBase::CreateObstacle(float4::Right, RoundRenderOrder::Obstacle1);

	CreateActor<RoundA_Enter_Sky>();
	CreateDoor();
	
	CreteaKey();
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
	Back->RenderReserve(2);
	Back->CreateRender("RoundA_Enter_BackGround.bmp", RoundRenderOrder::BackGround2);
}

void RoundAEnterLevel::CreateDoor()
{
	const float4 ScreenSize = GameEngineWindow::GetScreenSize();
	const float4 Pivot = float4{ ScreenSize.x * 0.5f, ScreenSize.y * 0.7f };
	const float4 Offset[3] = { {-150.f, 0.f} , {0.f,0.f}, {150.f, 0.f} };
	for (size_t i = 0; i < 3; ++i)
	{
		Door[i] = CreateActor<NextDoor>();
		Door[i]->SelectDoor(DoorType::Blue, { 200.f, 200.f }, RoundRenderOrder::Door);
		Door[i]->SetPos(Pivot + Offset[i]);
	}
}

void RoundAEnterLevel::CreteaKey()
{
	GameEngineInput::CreateKey("Door0", '1');
	GameEngineInput::CreateKey("Door1", '2');
	GameEngineInput::CreateKey("Door2", '3');
}

void RoundAEnterLevel::Update(float _DeltaTime)
{
	if (SelectedDoor < 0)
	{
		if (true == GameEngineInput::IsDown("Door0"))
		{
			SelectedDoor = 0;
		}
		else if (true == GameEngineInput::IsDown("Door1"))
		{
			SelectedDoor = 1;
		}
		else if (true == GameEngineInput::IsDown("Door2"))
		{
			SelectedDoor = 2;
		}
		return;
	}

	Door[SelectedDoor]->DoorOpen();
	NextLevelTime -= _DeltaTime;
	if (0 < NextLevelTime)
		return;

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
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	CreatePlayer(GetSelectCharacter());
	GetPlayer()->SetPos({ScreenSize.x * 0.2f, ScreenSize.y * 0.8f});
}

void RoundAEnterLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	RoundLevelBase::LevelChangeEnd(_NextLevel);

	for (size_t i = 0; i < 3; ++i)
	{
		Door[i]->Reset();
	}

	SelectedDoor = -1;
	NextLevelTime = 3.f;
}
