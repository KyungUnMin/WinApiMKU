#pragma once
#include <vector>
#include "BubbleMissleStateBase.h"

class BubbleDestination;

class BubbleStateMove : public BubbleMissleStateBase
{
public:
	static const float	MoveSpeed;

	BubbleStateMove();
	~BubbleStateMove();

	BubbleStateMove(const BubbleStateMove& _Other) = delete;
	BubbleStateMove(BubbleStateMove&& _Other) noexcept = delete;
	BubbleStateMove& operator=(const BubbleStateMove& _Other) = delete;
	BubbleStateMove& operator=(const BubbleStateMove&& _Other) noexcept = delete;

	inline BubbleDestination* GetNowDest()
	{
		return NowDest;
	}

protected:
	void Init(PlayerCharacterType _CharType, BubbleMissleType _BubbleType) override;
	void Update(float _DeltaTime) override;

	void EnterState() override;

private:
	BubbleDestination*			NowDest			= nullptr;

	void ResourceLoad();
	void CreateAnimation(PlayerCharacterType _CharType, BubbleMissleType _BubbleType);

	void MoveBubble(float _DeltaTime);
	void CheckDest();
};

