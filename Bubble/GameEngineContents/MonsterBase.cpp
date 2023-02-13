#include "MonsterBase.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include "MonsterFSM.h"
#include "PlayerBase.h"

const float4 MonsterBase::RenderScale		= float4{ 200.f, 200.f };
const float4 MonsterBase::CollisionScale		= float4{ 50.f, 50.f };
const float4 MonsterBase::CollisionOffset	= float4{ 0.f, -50.f };

MonsterBase::MonsterBase()
{
	FsmPtr = new MonsterFSM;
	FsmPtr->SetMonser(this);
}

MonsterBase::~MonsterBase()
{
	if (nullptr != FsmPtr)
	{
		delete FsmPtr;
		FsmPtr = nullptr;
	}
}

void MonsterBase::Start()
{
	MovableActor::Start();
	RenderPtr = CreateRender(RenderOrder::Monster1);
	RenderPtr->SetScale(RenderScale);

	CollisionPtr = CreateCollision(CollisionOrder::Monster);
	CollisionPtr->SetScale(CollisionScale);
	CollisionPtr->SetPosition(CollisionOffset);
}

void MonsterBase::Start_FSM(MonsterStateType _StartType)
{
	if (true == FsmPtr->States.empty())
	{
		MsgAssert("아직 몬스터의 FSM을 만들어주지 않았습니다");
		return;
	}

	FsmPtr->Start();
	FsmPtr->ChangeState(_StartType);
}



void MonsterBase::Update(float _DeltaTime)
{
	FsmPtr->Update(_DeltaTime);
}

void MonsterBase::Render(float _DeltaTime)
{
	FsmPtr->Render(_DeltaTime);
}


