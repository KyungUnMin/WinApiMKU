#include "BubbleMissle.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "BubbleMissleFSM.h"
#include "RoundLevelBase.h"
#include "BubbleStateMove.h"

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


void BubbleMissle::SetMoveSpeed(PlayerCharacterType _CharType)
{
	if (PlayerCharacterType::CORORON != _CharType)
		return;

	BubbleStateMove* MoveState = dynamic_cast<BubbleStateMove*>(FSM->GetState(BubbleStateType::Move));
	if (nullptr == MoveState)
	{
		MsgAssert("이 버블엔 Move상태가 없습니다");
	}
	
	MoveState->SetCororonSpeed();
}
