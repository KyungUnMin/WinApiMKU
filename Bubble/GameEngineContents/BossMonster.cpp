#include "BossMonster.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include "BossMonsterFSM.h"

const float4					BossMonster::RenderScale				= float4{ 200.f, 200.f };
const float4					BossMonster::CollisionScale			= float4{ 100.f, 100.f };

BossMonster::BossMonster()
{
	FsmPtr = new BossMonsterFSM(this);
}

BossMonster::~BossMonster()
{
	if (nullptr != FsmPtr)
	{
		delete FsmPtr;
		FsmPtr = nullptr;
	}
}

void BossMonster::Start()
{
	ResourceLoad();
	CreateComponent();
	CreateAnimation();

	FsmPtr->Start();
}


void BossMonster::CreateComponent()
{
	RenderPtr = CreateRender(RenderOrder::Monster1);
	RenderPtr->SetScale(RenderScale);
	
	CollisionPtr = CreateCollision(CollisionOrder::BossMonster);
	CollisionPtr->SetScale(CollisionScale);
}

void BossMonster::Update(float _DeltaTime)
{
	FsmPtr->Update(_DeltaTime);
}

void BossMonster::Render(float _DeltaTime)
{
	FsmPtr->Render(_DeltaTime);
}
