#include "MonsterMissle_WarurinBress.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>

const std::string MonsterMissle_WarurinBress::AniNames[2] =
{
	"Ready","Throw"
};

const float4 MonsterMissle_WarurinBress::RenderScale = float4{ 230.f, 230.f };


MonsterMissle_WarurinBress::MonsterMissle_WarurinBress()
{

}

MonsterMissle_WarurinBress::~MonsterMissle_WarurinBress()
{

}







void MonsterMissle_WarurinBress::Start()
{
	MonsterMissleBase::Start();
	ResourceLoad();

	ScreenSize = GameEngineWindow::GetScreenSize();
	GameEngineRender* RenderPtr = GetRender();
	RenderPtr->SetScale(RenderScale);

	std::string AniName;

	//Left_Ready
	AniName = "Left_" + AniNames[static_cast<int>(WB_State::Ready)];
	RenderPtr->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = LeftImagePath,
		.Start = 0,
		.End = 6,
		.InterTimer = 0.06f,
		.Loop = false
	});

	
	//Right_Ready
	AniName = "Right_" + AniNames[static_cast<int>(WB_State::Ready)];
	RenderPtr->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = RightImagePath,
		.Start = 0,
		.End = 6,
		.InterTimer = 0.06f,
		.Loop = false
	});



	//Left_Throw
	AniName = "Left_" + AniNames[static_cast<int>(WB_State::Throw)];
	RenderPtr->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = LeftImagePath,
		.Start = 7,
		.End = 8,
		.InterTimer = 0.1f,
		.Loop = true
	});


	//Right_Throw
	AniName = "Right_" + AniNames[static_cast<int>(WB_State::Throw)];
	RenderPtr->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = RightImagePath,
		.Start = 7,
		.End = 8,
		.InterTimer = 0.1f,
		.Loop = true
	});
}


void MonsterMissle_WarurinBress::ResourceLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("MonsterMissle");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftImagePath))->Cut(4, 3);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightImagePath))->Cut(4, 3);
	IsLoad = true;
}



void MonsterMissle_WarurinBress::SetDir(const float4& _Dir)
{
	MovableActor::SetDir(_Dir);

	int AniIndex = static_cast<int>(CurState);
	std::string  AniName = GetDirStr() + AniNames[AniIndex];
	GetRender()->ChangeAnimation(AniName);
}

void MonsterMissle_WarurinBress::ThrowMissle(const float4& _Dir)
{
	SetDir(_Dir);
	CurState = WB_State::Throw;

	int AniIndex = static_cast<int>(CurState);
	std::string  AniName = GetDirStr() + AniNames[AniIndex];
	GetRender()->ChangeAnimation(AniName);
}



void MonsterMissle_WarurinBress::Update(float _DeltaTime)
{
	if (WB_State::Ready == CurState)
		return;

	//장애물에 막힘없이 이동
	SetMove(GetDirVec() * MoveSpeed * _DeltaTime);

	//플레이어 충돌 처리
	PlayerCollisionCheck();

	//화면 밖으로 나갔을때 Death
	float4 Pos = GetPos();
	if (Pos.x < -ScreenOutOffset || ScreenSize.x + ScreenOutOffset < Pos.x)
	{
		Death();
	}
}



