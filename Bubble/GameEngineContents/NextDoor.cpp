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
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad();
		IsLoad = true;
	}

}

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
	if (nullptr == DoorRender)
	{
		MsgAssert("Door의 색상을 선택해주지 않았습니다");
		return;
	}

	DoorRender->SetScale(_Scale);
}


void NextDoor::CreateDoorAni(DoorType _SelectedDoor)
{
	if (nullptr == DoorRender)
	{
		MsgAssert("Door의 색상을 선택해주지 않았습니다");
		return;
	}

	DoorRender->CreateAnimation
	({
		.AnimationName = "Create",
		.ImageName = "NextDoor.bmp",
		.Start = static_cast<int>(_SelectedDoor),
		.End = static_cast<int>(_SelectedDoor) + 6,
		.InterTimer = 0.1f,
		.Loop = false
	});

	DoorRender->CreateAnimation
	({
		.AnimationName = "Open",
		.ImageName = "NextDoor.bmp",
		.Start = static_cast<int>(_SelectedDoor) + 6,
		.End = static_cast<int>(_SelectedDoor) + 10,
		.InterTimer = 0.1f,
	});

	DoorRender->CreateAnimation
	({
		.AnimationName = "Wait",
		.ImageName = "NextDoor.bmp",
		.Start = static_cast<int>(_SelectedDoor) + 10,
		.End = static_cast<int>(_SelectedDoor) + 13,
		.InterTimer = 0.1f,
		});

	DoorRender->ChangeAnimation("Create");
}


void NextDoor::Update(float _DeltaTime)
{
	if (nullptr == DoorRender)
	{
		MsgAssert("Door의 색상을 선택해주지 않았습니다");
		return;
	}

	if (true == IsOpened)
		return;

	//10, 24, 38 프레임일때만
	int Frame = DoorRender->GetFrame();
	if ((Frame - 10) % 14)
		return;

	IsOpened = true;
	DoorRender->ChangeAnimation("Wait");
}

void NextDoor::DoorOpen()
{
	if (true == IsOpened)
		return;

	/*
	* ChangeAnimation내부에서 같은 애니메이션 간의 이동은 막혀있음
	* 그래서 Open애니메이션 일때 이 함수가 호출되도 상관없음
	*/
	DoorRender->ChangeAnimation("Open");
}