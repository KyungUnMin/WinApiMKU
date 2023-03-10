#pragma once
#include "BubbleMissleStateBase.h"

class BubbleStatePop : public BubbleMissleStateBase
{
public:
	BubbleStatePop();
	~BubbleStatePop();

	BubbleStatePop(const BubbleStatePop& _Other) = delete;
	BubbleStatePop(BubbleStatePop&& _Other) noexcept = delete;
	BubbleStatePop& operator=(const BubbleStatePop& _Other) = delete;
	BubbleStatePop& operator=(const BubbleStatePop&& _Other) noexcept = delete;

protected:
	void Init(PlayerCharacterType _CharType, BubbleMissleType _BubbleType) override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static bool SfxOn;

	BubbleMissleType	BubbleType				= BubbleMissleType::Normal;
	const int					CreateWaterCount	= 5;
	const int					PopPoint					= 10;

	void ResourceLoad();
	void LoadSFX();
	void CreateNatureMissle();
};

