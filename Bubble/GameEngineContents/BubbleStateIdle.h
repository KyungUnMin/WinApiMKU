#pragma once
#include "BubbleMissleStateBase.h"

class RigidBody;

class BubbleStateIdle : public BubbleMissleStateBase
{
public:
	static const float	MoveSpeed;
	static const float4	MaxVelocity;

	BubbleStateIdle();
	~BubbleStateIdle();

	BubbleStateIdle(const BubbleStateIdle& _Other) = delete;
	BubbleStateIdle(BubbleStateIdle&& _Other) noexcept = delete;
	BubbleStateIdle& operator=(const BubbleStateIdle& _Other) = delete;
	BubbleStateIdle& operator=(const BubbleStateIdle&& _Other) noexcept = delete;

protected:
	void Init(PlayerCharacterType _CharType, BubbleMissleType _BubbleType) override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	RigidBody*	RigidPtr	= nullptr;
	float4			FinalDest	= float4::Zero;

	void CollisionEachOther();
};

