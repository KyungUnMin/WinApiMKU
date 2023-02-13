#include "ZenChan_Falling.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineRender.h>
#include "MonsterBase.h"
#include "Monster_ZenChan.h"


ZenChan_Falling::ZenChan_Falling()
{

}

ZenChan_Falling::~ZenChan_Falling()
{

}


void ZenChan_Falling::Start()
{
	CreateAnimation();
}


void ZenChan_Falling::CreateAnimation()
{
	GameEngineRender* RenderPtr = GetMonster()->GetRender();

	int StartIndex = (2 * 4);
	const int IndexCount = 4;
	const float Duration = 0.25f;

	std::string LeftAniName = MovableActor::LeftStr + FallingAniName.data();
	std::string RightAniName = MovableActor::RightStr + FallingAniName.data();

	//���� �ִϸ��̼� ����
	RenderPtr->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = Monster_ZenChan::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = Duration,
	});

	//������ �ִϸ��̼� ����
	RenderPtr->CreateAnimation
	({
		.AnimationName = RightAniName,
		.ImageName = Monster_ZenChan::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = Duration,
	});


	StartIndex = (6 * 4);
	LeftAniName = MovableActor::LeftStr + RageAniName.data();
	RightAniName = MovableActor::RightStr + RageAniName.data();


	//���� �г� �ִϸ��̼� ����
	RenderPtr->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = Monster_ZenChan::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = Duration,
	});

	//���� �г� �ִϸ��̼� ����
	RenderPtr->CreateAnimation
	({
		.AnimationName = RightAniName,
		.ImageName = Monster_ZenChan::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = Duration,
	});
}




void ZenChan_Falling::EnterState()
{

}


void ZenChan_Falling::Update(float _DeltaTime)
{

}


