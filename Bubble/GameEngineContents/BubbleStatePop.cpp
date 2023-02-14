#include "BubbleStatePop.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "BubbleMissle.h"
#include "MonsterBase.h"

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

	//���� Ÿ�Կ� ���� ���� ����
	switch (BubbleType)
	{
	case BubbleMissleType::Normal:
		break;
	case BubbleMissleType::Fire:
		break;
	case BubbleMissleType::Water:
		break;
	case BubbleMissleType::Electronic:
		break;
	case BubbleMissleType::Rainbow:
		break;
	case BubbleMissleType::Windy:
		break;
	case BubbleMissleType::Melody:
		break;
	default:
		break;
	}
}

void BubbleStatePop::Update(float _DeltaTime)
{
	if (false == GetBubble()->GetRender()->IsAnimationEnd())
		return;

	
	//�ϴ� �ӽ������� Deathó������
	// ���߿� Ǯ�� ó���Ҳ��� �׶� �ٲ���
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
