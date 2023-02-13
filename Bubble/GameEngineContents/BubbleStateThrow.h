#pragma once
#include "BubbleMissleStateBase.h"

class BubbleStateThrow : public BubbleMissleStateBase
{
public:
	static const float MoveSpeed;

	BubbleStateThrow();
	~BubbleStateThrow();

	BubbleStateThrow(const BubbleStateThrow& _Other) = delete;
	BubbleStateThrow(BubbleStateThrow&& _Other) noexcept = delete;
	BubbleStateThrow& operator=(const BubbleStateThrow& _Other) = delete;
	BubbleStateThrow& operator=(const BubbleStateThrow&& _Other) noexcept = delete;

protected:
	void Init(PlayerCharacterType _CharType, BubbleMissleType _BubbleType) override;
	void Update(float _DeltaTime) override;

private:

	void ResourceLoad();
	bool MonsterCollisionCheck();
};

