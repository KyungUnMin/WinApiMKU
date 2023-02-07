#pragma once
#include <vector>
#include "BubbleMissleStateBase.h"

class RigidBody;
class BubbleDestination;

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

	inline BubbleDestination* GetNowDest()
	{
		return NowDest;
	}

protected:
	void Init(PlayerCharacterType _CharType, BubbleMissleType _BubbleType) override;
	void Update(float _DeltaTime) override;

	void EnterState() override;

private:
	RigidBody*														RigidPtr			= nullptr;
	BubbleDestination*											NowDest			= nullptr;

	void ResourceLoad();
	void CreateAnimation(PlayerCharacterType _CharType, BubbleMissleType _BubbleType);

	bool CollisionWithPlayer();
	void MoveBubble(float _DeltaTime);
	void CheckDest();
	void CollisionEachOther();
};

