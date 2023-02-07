#pragma once
#include "BubbleMissleStateBase.h"

class RigidBody;

class BubbleStateIdle : public BubbleMissleStateBase
{
public:
	static const float MoveSpeed;

	BubbleStateIdle();
	~BubbleStateIdle();

	BubbleStateIdle(const BubbleStateIdle& _Other) = delete;
	BubbleStateIdle(BubbleStateIdle&& _Other) noexcept = delete;
	BubbleStateIdle& operator=(const BubbleStateIdle& _Other) = delete;
	BubbleStateIdle& operator=(const BubbleStateIdle&& _Other) noexcept = delete;

protected:
	void Init(PlayerCharacterType _CharType, BubbleMissleType _BubbleType) override;
	void Update(float _DeltaTime) override;

private:
	RigidBody* RigidPtr = nullptr;

	void ResourceLoad();
	bool CollisionWithPlayer();
	void RaiseBubble(float _DeltaTime);
	void CollisionEachOther();
};

