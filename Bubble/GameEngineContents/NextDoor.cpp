#include "NextDoor.h"
#include <vector>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include "RoundLevelBase.h"
#include "PlayerBase.h"
#include "PlayerFSM.h"


NextDoor::NextDoor()
{

}

NextDoor::~NextDoor()
{

}


void NextDoor::Start()
{
	//이 클래스 통틀어 처음에만 리소스 로드하기
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad();
		IsLoad = true;
	}
}


//이 클래스 최초로 리소스 받아오기
void NextDoor::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NextDoor.bmp"))->Cut(5, 9);
}


void NextDoor::SetScale(float4 _Scale)
{
	//예외처리
	if (nullptr == DoorRender)
	{
		MsgAssert("Door의 색상을 선택해주지 않았습니다");
		return;
	}

	DoorRender->SetScale(_Scale);
}


//문의 종류에 따라 애니메이션 지정
void NextDoor::CreateDoorAni(DoorType _DoorType)
{
	//예외처리
	if (nullptr == DoorRender)
	{
		MsgAssert("Door의 색상을 선택해주지 않았습니다");
		return;
	}

	//문 생성 애니메이션
	DoorRender->CreateAnimation
	({
		.AnimationName = "Create",
		.ImageName = "NextDoor.bmp",
		.Start = static_cast<int>(_DoorType),
		.End = static_cast<int>(_DoorType) + 6,
		.InterTimer = 0.1f,
		.Loop = false
	});

	//문 열기 애니메이션
	DoorRender->CreateAnimation
	({
		.AnimationName = "Open",
		.ImageName = "NextDoor.bmp",
		.Start = static_cast<int>(_DoorType) + 6,
		.End = static_cast<int>(_DoorType) + 10,
		.InterTimer = 0.1f,
	});

	//문이 열린후 기다리는 애니메이션
	DoorRender->CreateAnimation
	({
		.AnimationName = "Wait",
		.ImageName = "NextDoor.bmp",
		.Start = static_cast<int>(_DoorType) + 10,
		.End = static_cast<int>(_DoorType) + 13,
		.InterTimer = 0.1f,
	});

	//처음은 문 생성 애니메이션으로 지정
	DoorRender->ChangeAnimation("Create");
}



void NextDoor::Update(float _DeltaTime)
{
	//예외처리
	if (nullptr == DoorRender)
	{
		MsgAssert("Door의 색상을 선택해주지 않았습니다");
		return;
	}

	CreateLiveTime += _DeltaTime;

	//플레이어와 충돌처리
	CollisionPlayer();

	//애니메이션 처리
	DoorAnimation();

	//플레이어와 충돌했을시 플레이어 위치를 자신의 위치로 이동
	MovePlayer();
}


void NextDoor::CollisionPlayer()
{
	//이미 플레이어와 만났다면
	if (true == IsPlayerCollision)
		return;

	if (CreateLiveTime < CollisionOkTime)
		return;


	//플레이어와 이 문이 원 vs 점 충돌했을때만
	float4 PlayerPos = PlayerBase::MainPlayer->GetPos();
	float4 PlayerCollisionScale = PlayerBase::MainPlayer->CollisionScale;
	if (false == GameEngineCollision::CollisionCircleToPoint({ PlayerPos , PlayerCollisionScale }, { GetPos(), float4::Zero }))
		return;

	PlayerFSM* Fsm = PlayerBase::MainPlayer->GetFSM();
	Fsm->ChangeState(PlayerStateType::EnterDoor);
	PlayerColPos = PlayerPos;
	ColisionTime = CreateLiveTime;

	DoorOpen();
	IsPlayerCollision = true;
}

void NextDoor::DoorAnimation()
{
	//문이 이미 다 열린 상태라면 return
	if (true == IsOpenedValue)
		return;

	//여기까지 왔다면 문이 닫혀있거나 열리는 중

	//문이 다 열렸을때만 진행  (10, 24, 38 프레임일때만 return 아래 코드를 진행)
	//문이 닫힌 상태는 Frame이 10, 24, 38에 도달할 일이 없기 때문에 자동으로 return된다
	int Frame = DoorRender->GetFrame();
	if ((Frame - 10) % 14)
		return;

	//문이 다 열린 상태

	//다음 애니메이션(문이 전부 열려서 기다리고 있는 애니메이션)으로 이동
	IsOpenedValue = true;
	DoorRender->ChangeAnimation("Wait");
}



void NextDoor::DoorOpen()
{
	if (true == IsOpenedValue)
		return;

	/*
	* ChangeAnimation내부에서 같은 애니메이션 간의 이동은 막혀있음
	* 그래서 Open애니메이션 일때 이 함수가 여러번 호출되도 상관없음
	*/
	DoorRender->ChangeAnimation("Open");
}


void NextDoor::MovePlayer()
{
	if (false == IsPlayerCollision)
		return;

	//플레이어와 충돌한 후 흐른 시간
	float NowDuration = CreateLiveTime - ColisionTime;

	float Ratio = NowDuration / MoveDuration;

	float4 PlayerMovePos = float4::LerpClamp(PlayerColPos, GetPos(), Ratio);

	PlayerBase::MainPlayer->SetPos(PlayerMovePos);
}

//초기 상태로 되돌리기
void NextDoor::Reset()
{
	DoorRender->ChangeAnimation("Create", true);
	IsOpenedValue = false;
	IsPlayerCollision = false;
	CreateLiveTime = 0.f;
	ColisionTime = 0.f;
}

