#include "MonsterMissle_BossBeer.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "RoundLevelBase.h"

const std::string_view MonsterMissle_BossBeer::ImagePath			= "BossMissle.bmp";
const std::string_view MonsterMissle_BossBeer::ThrowAniName	= "Throw";
const std::string_view MonsterMissle_BossBeer::CrushAniName		= "Crush";

MonsterMissle_BossBeer::MonsterMissle_BossBeer()
{
}

MonsterMissle_BossBeer::~MonsterMissle_BossBeer()
{
}


void MonsterMissle_BossBeer::Start()
{
	MonsterMissleBase::Start();
	ResourceLoad();
	CreateAnimation();

	RoundLevel = dynamic_cast<RoundLevelBase*>(GetLevel());
	if (nullptr == RoundLevel)
	{
		MsgAssert("BossMissle이 RoundLevel이 아닌곳에서 생성되었습니다");
		return;
	}

}



void MonsterMissle_BossBeer::ResourceLoad()
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
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(ImagePath))->Cut(4, 3);
	IsLoad = true;
}

void MonsterMissle_BossBeer::CreateAnimation()
{
	GameEngineRender* RenderPtr = GetRender();
	RenderPtr->CreateAnimation
	({
		.AnimationName = ThrowAniName,
		.ImageName = ImagePath,
		.Start = 0,
		.End = 7
	});

	RenderPtr->CreateAnimation
	({
		.AnimationName = CrushAniName,
		.ImageName = ImagePath,
		.Start = 8,
		.End = 11,
		.InterTimer = 0.15f,
		.Loop = false
	});

	RenderPtr->ChangeAnimation(ThrowAniName);
}




void MonsterMissle_BossBeer::Update(float _DeltaTime)
{
	switch (CurState)
	{
	case MonsterMissle_BossBeer::State::Throw:
		ThrowMove(_DeltaTime);
		break;
	case MonsterMissle_BossBeer::State::Crush:
		WaitingCrush();
		break;
	}
}



void MonsterMissle_BossBeer::ThrowMove(float _DeltaTime)
{
	float4 NextPos = GetPos() + (MoveDir * MoveSpeed * _DeltaTime);
	float4 CheckPos = NextPos + MoveDir * MonsterMissleBase::CollisionScale.half();

	if (false == RoundLevel->IsBlockPos(CheckPos))
	{
		SetPos(NextPos);
		PlayerCollisionCheck();
		return;
	}

	CurState = State::Crush;
	GetRender()->ChangeAnimation(CrushAniName);
}

void MonsterMissle_BossBeer::WaitingCrush()
{
	if (false == GetRender()->IsAnimationEnd())
		return;

	Death();
}

