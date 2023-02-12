#include "ZenChan_Move.h"
#include <GameEngineCore/GameEngineRender.h>
#include "MonsterBase.h"
#include "Monster_ZenChan.h"

ZenChan_Move::ZenChan_Move()
{

}

ZenChan_Move::~ZenChan_Move()
{

}

void ZenChan_Move::Start()
{
	GameEngineRender* RenderPtr = GetMonster()->GetRender();

	int StartIndex = 0;
	const int IndexCount = 4;
	const float Duration = 0.25f;

	std::string LeftAniName = MovableActor::LeftStr + MoveAniName.data();
	std::string RightAniName = MovableActor::RightStr + MoveAniName.data();

	//哭率 局聪皋捞记 积己
	RenderPtr->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = Monster_ZenChan::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = Duration,
	});

	//坷弗率 局聪皋捞记 积己
	RenderPtr->CreateAnimation
	({
		.AnimationName = RightAniName,
		.ImageName = Monster_ZenChan::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = Duration,
	});

	
	StartIndex = (4 * 4);
	LeftAniName = MovableActor::LeftStr + RageAniName.data();
	RightAniName = MovableActor::RightStr + RageAniName.data();


	//哭率 盒畴 局聪皋捞记 积己
	RenderPtr->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = Monster_ZenChan::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = Duration,
	});

	//哭率 盒畴 局聪皋捞记 积己
	RenderPtr->CreateAnimation
	({
		.AnimationName = RightAniName,
		.ImageName = Monster_ZenChan::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = Duration,
	});
}

void ZenChan_Move::EnterState()
{
	GameEngineRender* RenderPtr = GetMonster()->GetRender();
	std::string LeftAniName = MovableActor::LeftStr + MoveAniName.data();
	RenderPtr->ChangeAnimation(LeftAniName);
}


void ZenChan_Move::Update(float _DeltaTime)
{
	int a = 0;
}