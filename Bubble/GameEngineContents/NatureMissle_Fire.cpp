#include "NatureMissle_Fire.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "MonsterBase.h"
#include "PlayerBase.h"
#include "PlayerFSM.h"

const std::string_view	NatureMissle_Fire::ImagePath	= "Fire.bmp";
const float4					NatureMissle_Fire::FallColScale	= float4{ 10.f, 10.f };
const std::string_view	NatureMissle_Fire::AniNames[3]	= 
{
	"Fire_Fall",
	"Fire_Burn" ,
	"Fire_Extinguish" 
};

float NatureMissle_Fire::PrevPlayerColTime = 0.f;

NatureMissle_Fire::NatureMissle_Fire()
{

}

NatureMissle_Fire::~NatureMissle_Fire()
{

}

void NatureMissle_Fire::Start()
{
	NatureMissleBase::Start();
	ResourceLoad();
	CreateAnimation();
}



void NatureMissle_Fire::ResourceLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("NatureMissle");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(ImagePath))->Cut(4, 3);
	IsLoad = true;
}


void NatureMissle_Fire::CreateAnimation()
{
	GameEngineRender* RenderPtr = GetRender();
	RenderPtr->CreateAnimation
	({
		.AnimationName = AniNames[static_cast<int>(State::Fall)],
		.ImageName = ImagePath,
		.Start = 0,
		.End = 3,
	});

	RenderPtr->CreateAnimation
	({
		.AnimationName = AniNames[static_cast<int>(State::Burn)],
		.ImageName = ImagePath,
		.Start = 4,
		.End = 7,
	});

	RenderPtr->CreateAnimation
	({
		.AnimationName = AniNames[static_cast<int>(State::Extinguish)],
		.ImageName = ImagePath,
		.Start = 8,
		.End = 11,
		.Loop = false
	});

	ChangeState(State::Fall);
}


void NatureMissle_Fire::ChangeState(State _NextState)
{
	NowState = _NextState;
	GetRender()->ChangeAnimation(AniNames[static_cast<int>(NowState)]);
}








void NatureMissle_Fire::Update(float _DeltaTime)
{
	switch (NowState)
	{
	case NatureMissle_Fire::Fall:
		Update_Fall(_DeltaTime);
		break;
	case NatureMissle_Fire::Burn:
		Update_Burn(_DeltaTime);
		break;
	case NatureMissle_Fire::Extinguish:
		Update_Extinguish(_DeltaTime);
		break;
	}
}



void NatureMissle_Fire::Update_Fall(float _DeltaTime)
{
	if (true == IsGround(FallColScale))
	{
		RaiseOnGround(NatureMissleBase::CollisionScale);
		ChangeState(State::Burn);
		return;
	}

	//아래로 이동
	SetMove(float4::Down * FallSpeed * _DeltaTime);

	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	if (GetPos().y < (ScreenSize.y + 50.f))
		return;

	Death();
}

void NatureMissle_Fire::Update_Burn(float _DeltaTime)
{
	BurnTimer += _DeltaTime;
	if (ExtinguishTime < BurnTimer)
	{
		ChangeState(State::Extinguish);
		return;
	}

	CollisionCheck();
}


void NatureMissle_Fire::CollisionCheck()
{
	//몬스터와의 충돌체크
	static std::vector<MonsterBase*> Monsters;
	if (true == CollisionCheckWithMonster(Monsters))
	{
		for (MonsterBase* Monster : Monsters)
		{
			Monster->DeathFromNature(this);
		}
	}



	if (nullptr == PlayerBase::MainPlayer)
	{
		PrevPlayerColTime = 0.f;
		return;
	}


	//플레이어와 충돌하고 난 후 경과된 시간이 
	//InvalidPlayerColTime만큼 지나지 않았다면 플레이어와 충돌처리를 하지않음
	float PlayerAliveTime = PlayerBase::MainPlayer->GetAliveTime();
	if (PlayerAliveTime < (PrevPlayerColTime + InvalidPlayerColTime))
		return;


	//플레이어와의 충돌체크
	if (true == CollisionCheckWithPlayer())
	{
		PlayerFSM* PlayerFsm = PlayerBase::MainPlayer->GetFSM();
		PlayerStateType PlayerState = PlayerFsm->GetCurStateByEnum();

		if (
			(PlayerStateType::Embarrassed != PlayerState)
			&& (PlayerStateType::Damaged != PlayerState)
			//&& (PlayerStateType::Jump != PlayerState)
			)
		{
			PrevPlayerColTime = PlayerAliveTime;
			PlayerBase::MainPlayer->GetFSM()->ChangeState(PlayerStateType::Embarrassed);
		}
	}

}

void NatureMissle_Fire::Update_Extinguish(float _DeltaTime)
{
	if (false == GetRender()->IsAnimationEnd())
		return;

	Death();
}



