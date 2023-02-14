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
	//�ִϸ��̼��� ���� ������ �ʰ� ������ ����ߴ� Move�ִϸ��̼� �״�� �̿�
	SetAniName("Move");

	//RigidBody�� ������ ����
	RigidPtr->SetOwner(GetBubble());
}


void BubbleStateIdle::EnterState()
{
	BubbleMissleStateBase::EnterState();
	FinalDest = GetBubble()->GetPos();
}

void BubbleStateIdle::Update(float _DeltaTime)
{
	//�÷��̾�� �浹 ���� Ȯ��
	PlayerCollisionCheck();

	float4 NowPos = GetBubble()->GetPos();
	float4 Dir = FinalDest - NowPos;
	if (false == Dir.IsZero())
	{
		Dir.Normalize();
		GetBubble()->SetMove(Dir * MoveSpeed * _DeltaTime);
	}

	DragMonster();

	//���� ���ΰ��� �浹ó��
	CollisionEachOther();

	//�浹ü ������Ʈ(������ �������� �̵�)
	RigidPtr->Update(_DeltaTime);
}

void BubbleStateIdle::CollisionEachOther()
{
	//����鳢�� �浹�Ҷ���
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

		//���ۿ���� += (����->�ڽ� ������ ����)
		ReactionDir += Pos - OtherActor->GetPos();
	}

	if (true == ReactionDir.IsZero())
		return;

	ReactionDir.Normalize();
	float4 ColSize = BubbleMissle::CollisionScale;
	RigidPtr->SetVelocity(ReactionDir * ColSize.Size());
}


