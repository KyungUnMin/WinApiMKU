#include "MonsterMissle_HidegonsBress.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "RoundLevelBase.h"

const std::string MonsterMissle_HidegonsBress::AniNames[2] =
{
	"Throw",
	"Attach"
};

const float4 MonsterMissle_HidegonsBress::RenderScale = float4{ 230.f, 230.f };

MonsterMissle_HidegonsBress::MonsterMissle_HidegonsBress()
{

}

MonsterMissle_HidegonsBress::~MonsterMissle_HidegonsBress()
{

}



void MonsterMissle_HidegonsBress::Start()
{
	MonsterMissleBase::Start();
	ResourceLoad();
	CreateAnimation();
	RoundLevel = GetRoundLevel();
}


void MonsterMissle_HidegonsBress::ResourceLoad()
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
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftImagePath))->Cut(5, 3);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightImagePath))->Cut(5, 3);
	IsLoad = true;
}

void MonsterMissle_HidegonsBress::CreateAnimation()
{
	GameEngineRender* RenderPtr = GetRender();
	RenderPtr->SetScale(RenderScale);

	const float ThrowAniDuration = 0.05f;
	const float AttachAniDuration = 0.1f;
	std::string AniName;

	//Left_Throw
	AniName = "Left_" + AniNames[static_cast<int>(HB_State::Throw)];
	RenderPtr->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = LeftImagePath,
		.Start = 0,
		.End = 11,
		.InterTimer = ThrowAniDuration,
		.Loop = false
	});


	//Left_Throw
	AniName = "Right_" + AniNames[static_cast<int>(HB_State::Throw)];
	RenderPtr->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = RightImagePath,
		.Start = 0,
		.End = 11,
		.InterTimer = ThrowAniDuration,
		.Loop = false
	});


	//Left_Attack
	AniName = "Left_" + AniNames[static_cast<int>(HB_State::Attach)];
	RenderPtr->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = LeftImagePath,
		.Start = 12,
		.End = 14,
		.InterTimer = AttachAniDuration,
		.Loop = false
	});


	//Right_Attack
	AniName = "Right_" + AniNames[static_cast<int>(HB_State::Attach)];
	RenderPtr->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = RightImagePath,
		.Start = 12,
		.End = 14,
		.InterTimer = AttachAniDuration,
		.Loop = false
	});

	RenderPtr->Off();
}






void MonsterMissle_HidegonsBress::ThrowMissle(const float4& _Dir)
{
	GetRender()->On();

	SetDir(_Dir);
	ChangeNowStateAni();
}

void MonsterMissle_HidegonsBress::ChangeNowStateAni()
{
	int AniIndex = static_cast<int>(CurState);
	std::string  AniName = GetDirStr() + AniNames[AniIndex];
	GetRender()->ChangeAnimation(AniName);
}


void MonsterMissle_HidegonsBress::Update(float _DeltaTime)
{
	if (HB_State::Attach == CurState)
	{
		if (true == GetRender()->IsAnimationEnd())
		{
			Death();
		}
		
		return;
	}
	
	float4 PrevPos = GetPos();
	if (false == MoveHorizon(MoveSpeed, MonsterMissleBase::CollisionScale, _DeltaTime))
	{
		CurState = HB_State::Attach;
		ChangeNowStateAni();
		return;
	}

	//Missle이 이동하는 경로 사이에 벽이 있었다면 Attach상태로 변경
	float4 NowPos = GetPos();
	int MoveLength = abs(NowPos.ix() - PrevPos.ix());
	
	for (int i = 0; i < MoveLength; ++i)
	{
		float4 CheckPos = PrevPos + (GetDirVec() * i);
		if (false == RoundLevel->IsBlockPos(CheckPos))
			continue;

		SetPos(CheckPos);
		CurState = HB_State::Attach;
		ChangeNowStateAni();
		return;
	}

	//플레이어 충돌 처리
	PlayerCollisionCheck();
}
