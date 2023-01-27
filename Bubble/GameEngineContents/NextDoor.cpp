#include "NextDoor.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>

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

	//문이 이미 다 열린 상태라면 return
	if (true == IsOpened)
		return;

	//여기까지 왔다면 문이 닫혀있거나 열리는 중
	
	//문이 다 열렸을때만 진행  (10, 24, 38 프레임일때만 return 아래 코드를 진행)
	//문이 닫힌 상태는 Frame이 10, 24, 38에 도달할 일이 없기 때문에 자동으로 return된다
	int Frame = DoorRender->GetFrame();
	if ((Frame - 10) % 14)
		return;

	//문이 다 열린 상태

	//다음 애니메이션(문이 전부 열려서 기다리고 있는 애니메이션)으로 이동
	IsOpened = true;
	DoorRender->ChangeAnimation("Wait");
}

void NextDoor::DoorOpen()
{
	if (true == IsOpened)
		return;

	/*
	* ChangeAnimation내부에서 같은 애니메이션 간의 이동은 막혀있음
	* 그래서 Open애니메이션 일때 이 함수가 여러번 호출되도 상관없음
	*/
	DoorRender->ChangeAnimation("Open");
}

//초기 상태로 되돌리기
void NextDoor::Reset()
{
	DoorRender->ChangeAnimation("Create");
	IsOpened = false;
}

