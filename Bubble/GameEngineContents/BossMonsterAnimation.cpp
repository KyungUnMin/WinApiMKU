#include "BossMonster.h"
#include <string>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>

const std::string_view	BossMonster::RightImagePath		= "Right_Boss.bmp";
const std::string_view	BossMonster::LeftImagePath			= "Left_Boss.bmp";
const std::string_view	BossMonster::DeadImagePath		= "Boss_Dead.bmp";

const std::string_view	BossMonster::IdleAniName			= "Idle";
const std::string_view	BossMonster::AngryAniName			= "Angry";
const std::string_view	BossMonster::RageAngryAniName	= "Angry_Rage";
const std::string_view	BossMonster::LockAniName			= "Lock";
const std::string_view	BossMonster::DeadAniName			= "Dead";



void BossMonster::ResourceLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Monster");
	Dir.Move("Boss");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightImagePath))->Cut(4, 2);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftImagePath))->Cut(4, 2);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(DeadImagePath))->Cut(6, 1);
	IsLoad = true;
}


void BossMonster::CreateAnimation()
{
	std::string AniName = "";

	//---------------[Idle]-------------------

	//오른쪽 Idle애니메이션
	AniName = MovableActor::RightStr;
	AniName += IdleAniName;
	RenderPtr->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = RightImagePath,
		.Start = 0,
		.End = 3,
		.InterTimer = 0.1f,
		.Loop = true
	});

	//왼쪽 Idle애니메이션
	AniName = MovableActor::LeftStr;
	AniName += IdleAniName;
	RenderPtr->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = LeftImagePath,
		.Start = 0,
		.End = 3,
		.InterTimer = 0.1f,
		.Loop = true
	});


	//---------------[Angry]-------------------
	
	//오른쪽 Angry애니메이션
	AniName = MovableActor::RightStr;
	AniName += AngryAniName;
	RenderPtr->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = RightImagePath,
		.Start = 4,
		.End = 5,
		.InterTimer = 0.1f,
		.Loop = true
	});

	//왼쪽 Angry애니메이션
	AniName = MovableActor::LeftStr;
	AniName += AngryAniName;
	RenderPtr->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = LeftImagePath,
		.Start = 4,
		.End = 5,
		.InterTimer = 0.1f,
		.Loop = true
	});

	//---------------[Angry_Rage]-------------------
	
	//오른쪽 Angry애니메이션
	AniName = MovableActor::RightStr;
	AniName += RageAngryAniName;
	RenderPtr->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = RightImagePath,
		.Start = 6,
		.End = 7,
		.InterTimer = 0.1f,
		.Loop = true
	});

	//왼쪽 Angry애니메이션
	AniName = MovableActor::LeftStr;
	AniName += RageAngryAniName;
	RenderPtr->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = LeftImagePath,
		.Start = 6,
		.End = 7,
		.InterTimer = 0.1f,
		.Loop = true
	});

	//---------------[Lock]-------------------
	
	RenderPtr->CreateAnimation
	({
		.AnimationName = LockAniName,
		.ImageName = DeadImagePath,
		.Start = 0,
		.End = 1,
		.InterTimer = 0.25f,
		.Loop = true
	});

	//---------------[Dead]-------------------

	RenderPtr->CreateAnimation
	({
		.AnimationName = DeadAniName,
		.ImageName = DeadImagePath,
		.Start = 2,
		.End = 5,
		.InterTimer = 0.1f,
		.Loop = true
	});
}