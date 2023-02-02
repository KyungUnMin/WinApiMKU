#include "MonsterBase.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"

MonsterBase::MonsterBase()
{

}

MonsterBase::~MonsterBase()
{

}

void MonsterBase::Start()
{
	//이 클래스 통틀어 처음에만 리소스 로드하기
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad();
		IsLoad = true;
	}

	GameEngineRender* Render = CreateRender(RoundRenderOrder::Monster1);
	Render->CreateAnimation
	({
		.AnimationName = "Move",
		.ImageName = "LeftMove.bmp",
		.Start = 0,
		.End = 3,
		.InterTimer = 0.25f,
	});

	Render->SetScale({ 150.f ,150.f });
	Render->ChangeAnimation("Move");

	CollisionPtr = CreateCollision(CollisionOrder::Monster);
	CollisionPtr->SetScale({ 50.f, 50.f });
	CollisionPtr->SetPosition({ 0.f, -20.f });
}

void MonsterBase::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Monster");
	Dir.Move("ZenChan");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LeftMove.bmp"))->Cut(4, 1);
}

void MonsterBase::Update(float _DeltaTime)
{
	/*if (false == CollisionPtr->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player_Missle) }))
		return;

	Off();*/
}