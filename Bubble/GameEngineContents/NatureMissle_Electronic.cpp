#include "NatureMissle_Electronic.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "MonsterBase.h"
#include "PlayerBase.h"
#include "PlayerFSM.h"

const std::string_view NatureMissle_Electronic::ImagePath			= "Electronic.bmp";
const std::string_view NatureMissle_Electronic::MoveAniName		= "Move";
const std::string_view NatureMissle_Electronic::AttachAniName	= "Attach";

NatureMissle_Electronic::NatureMissle_Electronic()
{

}

NatureMissle_Electronic::~NatureMissle_Electronic()
{

}







void NatureMissle_Electronic::Start()
{
	NatureMissleBase::Start();
	ResourceLoad();
	CreateAnimation();
	ScreenSize = GameEngineWindow::GetScreenSize();
}


void NatureMissle_Electronic::ResourceLoad()
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
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(ImagePath))->Cut(3, 2);
	IsLoad = true;
}

void NatureMissle_Electronic::CreateAnimation()
{
	GameEngineRender* RenderPtr = GetRender();
	RenderPtr->CreateAnimation
	({
		.AnimationName = MoveAniName,
		.ImageName = ImagePath,
		.Start = 0,
		.End = 2
	});

	RenderPtr->CreateAnimation
	({
		.AnimationName = AttachAniName,
		.ImageName = ImagePath,
		.Start = 3,
		.End = 5,
		.InterTimer = 0.3f,
		.Loop = false
	});

	RenderPtr->ChangeAnimation(MoveAniName);
}









void NatureMissle_Electronic::Update(float _DeltaTime)
{
	switch (NowState)
	{
	case NatureMissle_Electronic::State::Move:
		Update_Move(_DeltaTime);
		break;
	case NatureMissle_Electronic::State::PlayerAttach:
		Update_Attach(_DeltaTime);
		break;
	}

	MonsterKill();
}


void NatureMissle_Electronic::Update_Move(float _DeltaTime)
{
	//플레이어와 충돌체크(플레이어와의 충돌은 딱 한번만 이루어짐)
	if (false == IsPlayerAttached && true == CollisionCheckWithPlayer())
	{
		GetRender()->ChangeAnimation(AttachAniName, true);
		NowState = State::PlayerAttach;
		IsPlayerAttached = true;
		PlayerBase::MainPlayer->GetFSM()->ChangeState(PlayerStateType::Embarrassed);
		return;
	}

	//화면 밖으로 나간 경우엔 삭제
	float4 ThisPos = GetPos();
	if ((ThisPos.x < -ScreenOutOffset) || ((ScreenSize.x + ScreenOutOffset) < ThisPos.x))
	{
		Death();
		return;
	}

	//이동
	SetMove(GetDirVec() * MoveSpeed * _DeltaTime);
}

void NatureMissle_Electronic::Update_Attach(float _DeltaTime)
{
	if (false == GetRender()->IsAnimationEnd())
		return;

	NowState = State::Move;
	GetRender()->ChangeAnimation(MoveAniName, true);
}

void NatureMissle_Electronic::MonsterKill()
{
	static std::vector<MonsterBase*> CollisionMonsters;
	if (false == CollisionCheckWithMonster(CollisionMonsters))
		return;

	for (MonsterBase* Monster : CollisionMonsters)
	{
		Monster->DeathFromNature(this);
	}
}
