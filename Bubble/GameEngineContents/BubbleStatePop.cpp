#include "BubbleStatePop.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "BubbleMissle.h"
#include "MonsterBase.h"
#include "PlayerBase.h"
#include "PointPannel.h"

#include "NatureMissle_Electronic.h"
#include "NatureMissle_Water.h"
#include "NatureMissle_Rainbow.h"
#include "NatureMissle_Fire.h"
#include "NatureMissle_Windy.h"

bool BubbleStatePop::SfxOn = false;

BubbleStatePop::BubbleStatePop()
{

}

BubbleStatePop::~BubbleStatePop()
{
	if (true == SfxOn)
	{
		SfxOn = false;
	}
}

void BubbleStatePop::Init(PlayerCharacterType _CharType, BubbleMissleType _BubbleType)
{
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad();
		LoadSFX();
		IsLoad = true;
	}

	SetAniName("Pop");

	GameEngineRender* Render = GetBubble()->GetRender();
	Render->CreateAnimation
	({
		.AnimationName = GetAniName(),
		.ImageName = "BubblePop.bmp",
		.Start = 0,
		.End = 3,
		.InterTimer = 0.1f,
		.Loop = false
	});

	BubbleType = _BubbleType;
}

void BubbleStatePop::EnterState()
{
	BubbleMissleStateBase::EnterState();

	MonsterBase* CatchTarget = GetBubble()->GetCatchTarget();
	if (nullptr != CatchTarget)
	{
		CatchTarget->DeathFromBubble();
		GetBubble()->SetCatchTarget(nullptr);
	}

	GetBubble()->GetCollisionPtr()->Off();

	//버블 타입에 따라 무언가 생성
	CreateNatureMissle();
	PointPannel::AddPoint(PopPoint);

	if (false == SfxOn)
	{
		GameEngineResources::GetInst().SoundPlay("BubblePop.mp3");
		SfxOn = true;
	}
}

void BubbleStatePop::Update(float _DeltaTime)
{
	if (false == GetBubble()->GetRender()->IsAnimationEnd())
		return;

	GetBubble()->Death();
}



void BubbleStatePop::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Bubble");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BubblePop.bmp"))->Cut(4, 1);
}

void BubbleStatePop::LoadSFX()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");
	Dir.Move("SFX");
	Dir.Move("Bubble");
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("BubblePop.mp3"));
}

void BubbleStatePop::CreateNatureMissle()
{
	//임시
	if (BubbleMissleType::Normal == BubbleType)
		return;


	/*if (BubbleMissleType::Windy == BubbleType)
		return;*/


	NatureMissleBase* NatureMissle = nullptr;
	BubbleMissle* Bubble = GetBubble();

	switch (BubbleType)
	{
	case BubbleMissleType::Fire:
		NatureMissle = Bubble->GetLevel()->CreateActor<NatureMissle_Fire>(UpdateOrder::Nature_Missle);
		break;
	case BubbleMissleType::Water:
	{
		float4 PlayerDir = PlayerBase::MainPlayer->GetDirVec();
		NatureMissle_Water* WaterMissle = Bubble->GetLevel()->CreateActor<NatureMissle_Water>(UpdateOrder::Nature_Missle);
		WaterMissle->SetCreateCount(CreateWaterCount);
		WaterMissle->InitPos(Bubble->GetPos(), {-PlayerDir.x, PlayerDir.y});
	}
		return;
	case BubbleMissleType::Electronic:
		NatureMissle = Bubble->GetLevel()->CreateActor<NatureMissle_Electronic>(UpdateOrder::Nature_Missle);
		break;
	case BubbleMissleType::Rainbow:
		NatureMissle = Bubble->GetLevel()->CreateActor<NatureMissle_Rainbow>(UpdateOrder::Nature_Missle);
		break;
	case BubbleMissleType::Windy:
		NatureMissle = Bubble->GetLevel()->CreateActor<NatureMissle_Windy>(UpdateOrder::Nature_Missle);
		break;
	}

	NatureMissle->SetPos(Bubble->GetPos());
}
