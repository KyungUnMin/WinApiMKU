#include "BubbleStatePop.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "BubbleMissle.h"
#include "MonsterBase.h"

#include "NatureMissle_Electronic.h"
#include "NatureMissle_Water.h"

BubbleStatePop::BubbleStatePop()
{

}

BubbleStatePop::~BubbleStatePop()
{

}

void BubbleStatePop::Init(PlayerCharacterType _CharType, BubbleMissleType _BubbleType)
{
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad();
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
}

void BubbleStatePop::Update(float _DeltaTime)
{
	if (false == GetBubble()->GetRender()->IsAnimationEnd())
		return;

	
	//일단 임시적으로 Death처리하자
	// 나중에 풀링 처리할꺼면 그때 바꾸자
	//GetBubble()->Off();
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

void BubbleStatePop::CreateNatureMissle()
{
	//임시
	if (BubbleMissleType::Normal == BubbleType)
		return;

	if (BubbleMissleType::Fire== BubbleType)
		return;

	if (BubbleMissleType::Rainbow == BubbleType)
		return;

	if (BubbleMissleType::Windy == BubbleType)
		return;

	/*if (BubbleMissleType::Water == BubbleType)
		return;*/


	NatureMissleBase* NatureMissle = nullptr;
	BubbleMissle* Bubble = GetBubble();

	switch (BubbleType)
	{
	case BubbleMissleType::Fire:
		break;
	case BubbleMissleType::Water:
	{
		const size_t WaterCnt = 10;
		for (size_t i = 0; i < WaterCnt; ++i)
		{
			NatureMissle_Water* WaterMissle = Bubble->GetLevel()->CreateActor<NatureMissle_Water>(UpdateOrder::Nature_Missle);
			WaterMissle->InitPos(Bubble->GetPos());
		}
	}
		break;
	case BubbleMissleType::Electronic:
		NatureMissle = Bubble->GetLevel()->CreateActor<NatureMissle_Electronic>(UpdateOrder::Nature_Missle);
		NatureMissle->SetPos(Bubble->GetPos());
		break;
	case BubbleMissleType::Rainbow:
		break;
	case BubbleMissleType::Windy:
		break;
	}

}
