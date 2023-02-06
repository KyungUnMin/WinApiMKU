#include "BubbleStatePop.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "BubbleMissle.h"

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
}

void BubbleStatePop::EnterState()
{
	BubbleMissleStateBase::EnterState();

	//TODO
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
