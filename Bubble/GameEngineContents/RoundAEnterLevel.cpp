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

const std::vector<float4> RoundAEnterLevel::PlayerSpanwPos = { { 100.f, 700.f } };

RoundAEnterLevel::RoundAEnterLevel()
{

}

RoundAEnterLevel::~RoundAEnterLevel()
{

}


void RoundAEnterLevel::Loading()
{
	//리소스 로드
	ResourceLoad();
	RoundLevelBase::LoadStage("AEnter", 1, 1);

	//뒤 배경과 레벨의 지형 생성
	CreateBackGround();
	RoundLevelBase::CreateStage(float4::Right, RoundRenderOrder::Obstacle1);

	//플레이어가 생성될 위치 설정
	SetPlayerSpawnPos(PlayerSpanwPos);

	//뒤쪽 좌우로 움직이는 하늘 생성
	CreateActor<RoundA_Enter_Sky>();
	//다음 레벨로 넘어가는 문 생성
	CreateDoor();
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

void RoundAEnterLevel::Update(float _DeltaTime)
{
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
