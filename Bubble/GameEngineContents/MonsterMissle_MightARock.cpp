#include "MonsterMissle_MightARock.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>

const std::string MonsterMissle_MightARock::AniNames[3] =
{
	"Gather","Throw","Crack"
};


MonsterMissle_MightARock::MonsterMissle_MightARock()
{

}

MonsterMissle_MightARock::~MonsterMissle_MightARock()
{

}



void MonsterMissle_MightARock::Start()
{
	MonsterMissleBase::Start();
	ResourceLoad();

	GameEngineRender* RenderPtr = GetRender();

	//Gather �ִϸ��̼�
	RenderPtr->CreateAnimation
	({
		.AnimationName = AniNames[static_cast<int>(MR_State::Gather)],
		.ImageName = ImagePath,
		.Start = 0,
		.End = 5,
		.InterTimer = 0.05f,
		.Loop = false
	});

	//Throw �ִϸ��̼�
	RenderPtr->CreateAnimation
	({
		.AnimationName = AniNames[static_cast<int>(MR_State::Throw)],
		.ImageName = ImagePath,
		.Start = 5,
		.End = 8,
		.InterTimer = 0.1f,
		.Loop = true
	});

	//Crack �ִϸ��̼�
	RenderPtr->CreateAnimation
	({
		.AnimationName = AniNames[static_cast<int>(MR_State::Crack)],
		.ImageName = ImagePath,
		.Start = 9,
		.End = 11,
		.InterTimer = 0.1f,
		.Loop = false
	});

	//Gather �ִϸ��̼� ����
	RenderPtr->ChangeAnimation(AniNames[static_cast<int>(CurState)]);
}


void MonsterMissle_MightARock::ResourceLoad()
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
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(ImagePath))->Cut(12, 1);
	IsLoad = true;
}




void MonsterMissle_MightARock::ThrowMissle(const float4& _Dir)
{
	SetDir(_Dir);
	CurState = MR_State::Throw;
	int AniIndex = static_cast<int>(CurState);
	GetRender()->ChangeAnimation(AniNames[AniIndex]);
}



void MonsterMissle_MightARock::Update(float _DeltaTime)
{
	if (MR_State::Gather == CurState)
		return;


	//Throw �ִϸ��̼��϶�
	if (MR_State::Throw == CurState)
	{
		if (false == MoveHorizon(MoveSpeed, CollisionScale, _DeltaTime))
		{
			CurState = MR_State::Crack;
			GetRender()->ChangeAnimation(AniNames[static_cast<int>(CurState)]);
			return;
		}

		PlayerCollisionCheck();
	}

	//Crack �ִϸ��̼��϶�
	else if (MR_State::Crack == CurState)
	{
		if (true == GetRender()->IsAnimationEnd())
		{
			Death();
			return;
		}
	}
	


}

