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
	//리소스 로드
	ResourceLoad();
	RoundLevelBase::LoadObstacle("AEnter", 1, 1);

	//뒤 배경과 레벨의 지형 생성
	CreateBackGround();
	RoundLevelBase::CreateObstacle(float4::Right, RoundRenderOrder::Obstacle1);

	//뒤쪽 좌우로 움직이는 하늘 생성
	CreateActor<RoundA_Enter_Sky>();
	//다음 레벨로 넘어가는 문 생성
	CreateDoor();
	
	//이 레벨에서 사용될 키 설정
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
	//추후에 충돌로 처리할 계획
	GameEngineInput::CreateKey("Door0", '1');
	GameEngineInput::CreateKey("Door1", '2');
	GameEngineInput::CreateKey("Door2", '3');
}

void RoundAEnterLevel::Update(float _DeltaTime)
{
	//문이 아직 선택되지 않았을때
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

	//문이 선택되었을때
	//해당 문을 여는 애니메이션을 작동시키고 NextLevelTime 시간만큼 대기
	Door[SelectedDoor]->DoorOpen();
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
	//이전 레벨(EnterRound)에서 LevelChangeEnd함수를 통해 이 씬의 SelectedCharacter를 설정해두었음
	//(그런데 안 좋은 방법인 것 같다, 추후에 변경할 것을 고려해보자)

	//캐릭터 생성 RoundLevelBase::SelectedCharacter 를 받아와서 캐릭터 생성
	CreatePlayer(GetSelectCharacter());

	//캐릭터 위치 설정
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	GetPlayer()->SetPos({ScreenSize.x * 0.2f, ScreenSize.y * 0.8f});
}

void RoundAEnterLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	//다음 레벨이 RoundLevelBase를 상속받았다면
	//그 레벨에 자신의 RoundLevelBase::SelectedCharacter를 바탕으로 캐릭터 생성
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
