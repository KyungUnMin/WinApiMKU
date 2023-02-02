#pragma once
#include "BubbleMissleBase.h"

class BubbleMissle_Normal : public BubbleMissleBase
{
public:
	BubbleMissle_Normal();
	~BubbleMissle_Normal();

	BubbleMissle_Normal(const BubbleMissle_Normal& _Other) = delete;
	BubbleMissle_Normal(BubbleMissle_Normal&& _Other) noexcept = delete;
	BubbleMissle_Normal& operator=(const BubbleMissle_Normal& _Other) = delete;
	BubbleMissle_Normal& operator=(const BubbleMissle_Normal&& _Other) noexcept = delete;

	void CreateAnimation(PlayerCharacterType _CharacterType) override;

protected:
	void Start() override;
	void BubblePop() override;

private:

};

