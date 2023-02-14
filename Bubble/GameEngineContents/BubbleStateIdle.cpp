#include "BubbleStateIdle.h"
#include <GameEngineCore/GameEngineCollision.h>
#include "BubbleMissle.h"
#include "RigidBody.h"

const float		BubbleStateIdle::MoveSpeed = 10.f;
const float4	BubbleStateIdle::MaxVelocity = float4{ 100.f, 100.f };

BubbleStateIdle::BubbleStateIdle()
{
	RigidPtr = new RigidBody;
	RigidPtr->SetMaxVelocity(MaxVelocity);
}

BubbleStateIdle::~BubbleStateIdle()
{
	if (nullptr != RigidPtr)
	{
		delete RigidPtr;
		RigidPtr = nullptr;
	}
}

void BubbleStateIdle::Init(PlayerCharacterType _CharType, BubbleMissleType _BubbleType)
{
	//애니메이션을 따로 만들지 않고 이전에 사용했던 Move애니메이션 그대로 이용
	SetAniName("Move");

	//RigidBody와 버블을 연결
	RigidPtr->SetOwner(GetBubble());
}


void BubbleStateIdle::EnterState()
{
	BubbleMissleStateBase::EnterState();
	FinalDest = GetBubble()->GetPos();
}

void BubbleStateIdle::Update(float _DeltaTime)
{
	//플레이어와 충돌 여부 확인
	PlayerCollisionCheck();

	float4 NowPos = GetBubble()->GetPos();
	float4 Dir = FinalDest - NowPos;
	if (false == Dir.IsZero())
	{
		Dir.Normalize();
		GetBubble()->SetMove(Dir * MoveSpeed * _DeltaTime);
	}

	DragMonster();

	//버블 서로간의 충돌처리
	CollisionEachOther();

	//충돌체 업데이트(버블의 실질적인 이동)
	RigidPtr->Update(_DeltaTime);
}

void BubbleStateIdle::CollisionEachOther()
{
	//버블들끼리 충돌할때만
	GameEngineCollision* CollisionPtr = GetBubble()->GetCollisionPtr();
	std::vector<GameEngineCollision*> Collisions;
	if (false == CollisionPtr->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player_Missle) }, Collisions))
		return;

	GameEngineActor* BubbleActor = GetBubble();
	float4 Pos = GetBubble()->GetPos();
	float4 Velocity = RigidPtr->GetVelocity();
	float4 ReactionDir = float4::Zero;

	for (size_t i = 0; i < Collisions.size(); ++i)
	{
		GameEngineActor* OtherActor = Collisions[i]->GetActor();
		if (OtherActor == BubbleActor)
			continue;

		//반작용방향 += (상대방->자신 방향의 벡터)
		ReactionDir += Pos - OtherActor->GetPos();
	}

	if (true == ReactionDir.IsZero())
		return;

	ReactionDir.Normalize();
	float4 ColSize = BubbleMissle::CollisionScale;
	RigidPtr->SetVelocity(ReactionDir * ColSize.Size());
}


