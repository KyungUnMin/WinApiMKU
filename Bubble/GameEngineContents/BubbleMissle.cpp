#include "BubbleMissle.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "BubbleMissleFSM.h"
#include "RoundLevelBase.h"

const float4 BubbleMissle::RenderScale = float4{ 150.f,150.f };
const float4 BubbleMissle::CollisionScale = float4{ 50.f,50.f };

BubbleMissle::BubbleMissle()
{
	FSM = new BubbleMissleFSM;
}

BubbleMissle::~BubbleMissle()
{
	if (nullptr != FSM)
	{
		delete FSM;
		FSM = nullptr;
	}
}

void BubbleMissle::Start()
{
	AniRender = CreateRender(RenderOrder::AttackBubble);
	AniRender->SetScale(RenderScale);
	CollisionPtr = CreateCollision(CollisionOrder::Player_Missle);
	CollisionPtr->SetScale(CollisionScale);
}


void BubbleMissle::Init(PlayerCharacterType _CharType, BubbleMissleType _BubbleType)
{
	FSM->Bubble = this;
	FSM->Start(_CharType, _BubbleType);
}



void BubbleMissle::Update(float _DeltaTime)
{
	FSM->Update(_DeltaTime);
}


