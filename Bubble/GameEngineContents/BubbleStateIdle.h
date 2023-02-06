#pragma once
#include "BubbleMissleStateBase.h"

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

	void ResourceLoad();
};

