#include "BubbleStateIdle.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "BubbleMissle.h"
#include "RoundLevelBase.h"

const float BubbleStateIdle::MoveSpeed = 100.f;

BubbleStateIdle::BubbleStateIdle()
{

}

BubbleStateIdle::~BubbleStateIdle()
{

}

void BubbleStateIdle::Init(PlayerCharacterType _CharType, BubbleMissleType _BubbleType)
{
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad();
		IsLoad = true;
	}

	int SelectCharIndex = static_cast<int>(_CharType) * 19;
	int Start = 0;
	int End = 0;

	if (_BubbleType == BubbleMissleType::Normal)
	{
		Start = End = SelectCharIndex;
	}
	else
	{
		Start = SelectCharIndex + (static_cast<int>(_BubbleType) - 1) * 3 + 1;
		End = Start + 2;
	}

	SetAniName("Idle");

	GameEngineRender* Render = GetBubble()->GetRender();
	Render->CreateAnimation
	({
		.AnimationName = GetAniName(),
		.ImageName = "BubbleIdle.bmp",
		.Start = Start,
		.End = End,
		.InterTimer = 0.25f,
	});
}

void BubbleStateIdle::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Bubble");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BubbleIdle.bmp"))->Cut(18, 4);
}

void BubbleStateIdle::Update(float _DeltaTime)
{
	BubbleMissle* Bubble = GetBubble();
	float4 NowPos = Bubble->GetPos();
	float4 NextPos = NowPos + float4::Up * MoveSpeed * _DeltaTime;

	/*if (false == Bubble->GetRoundLevel()->IsBlockPos(NextPos))
	{
		Bubble->SetPos(NextPos);
		return;
	}*/

	//юс╫ц
	if (NextPos.y < 100.f)
		return;

	Bubble->SetPos(NextPos);
}


