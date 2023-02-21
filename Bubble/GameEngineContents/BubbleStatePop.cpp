#include "BubbleStatePop.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "BubbleMissle.h"
#include "MonsterBase.h"

#include "NatureMissle_Electronic.h"

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

	if (BubbleMissleType::Normal == BubbleType)
		return;

	//���� Ÿ�Կ� ���� ���� ����
	CreateNatureMissle();
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

void BubbleStatePop::CreateNatureMissle()
{

	//�ӽ�
	if (BubbleMissleType::Electronic != BubbleType)
		return;


	NatureMissleBase* NatureMissle = nullptr;
	BubbleMissle* Bubble = GetBubble();

	switch (BubbleType)
	{
	case BubbleMissleType::Fire:
		break;
	case BubbleMissleType::Water:
		break;
	case BubbleMissleType::Electronic:
		NatureMissle = Bubble->GetLevel()->CreateActor<NatureMissle_Electronic>(UpdateOrder::Nature_Missle);
		break;
	case BubbleMissleType::Rainbow:
		break;
	case BubbleMissleType::Windy:
		break;
	}

	NatureMissle->SetPos(Bubble->GetPos());
}
