#include "ZenChan_Move.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineRender.h>
#include "MonsterBase.h"
#include "Monster_ZenChan.h"
#include "RoundLevelBase.h"
#include "ContentsEnum.h"

const float ZenChan_Move::MoveSpeed = 200.f;

ZenChan_Move::ZenChan_Move()
{

}

ZenChan_Move::~ZenChan_Move()
{

}

void ZenChan_Move::Start()
{
	CreateAnimation();
	
	RoundLevel = dynamic_cast<RoundLevelBase*>(GetMonster()->GetLevel());
	if (nullptr == RoundLevel)
	{
		MsgAssert("몬스터 FSM은 RoundLevelBase를 상속받은 레벨에서만 동작할 수 있습니다");
		return;
	}


}

void ZenChan_Move::CreateAnimation()
{
	GameEngineRender* RenderPtr = GetMonster()->GetRender();

	int StartIndex = 0;
	const int IndexCount = 4;
	const float Duration = 0.25f;

	std::string LeftAniName = MovableActor::LeftStr + MoveAniName.data();
	std::string RightAniName = MovableActor::RightStr + MoveAniName.data();

	//왼쪽 애니메이션 생성
	RenderPtr->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = Monster_ZenChan::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = Duration,
	});

	//오른쪽 애니메이션 생성
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


	//왼쪽 분노 애니메이션 생성
	RenderPtr->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = Monster_ZenChan::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = Duration,
	});

	//왼쪽 분노 애니메이션 생성
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

	SetNowAniName(MoveAniName);
	std::string RightAniName= GetMonster()->GetDirStr() + MoveAniName.data();

	RenderPtr->ChangeAnimation(RightAniName);
}




void ZenChan_Move::Update(float _DeltaTime)
{
	//float4 UnderPos = GetMonster()->GetPos() + float4::Down;
	//if (false == RoundLevel->IsBlockPos(UnderPos))
	//{
	//	//TODO
	//	return;
	//}
	
	//if (false == GetMonster()->IsGround(MonsterBase::CollisionScale))
	//{
	//	//TODO
	//	return;
	//}
	
	if (true == GetMonster()->MoveHorizon(MoveSpeed, MonsterBase::CollisionScale, _DeltaTime))
		return;

	ChangeDir();
}

void ZenChan_Move::ChangeDir()
{
	GetMonster()->SetReverseDir();

	std::string NextAniName = GetMonster()->GetDirStr();
	NextAniName += GetNowAniName();
	GetMonster()->GetRender()->ChangeAnimation(NextAniName);
}