#pragma once
#include "RoundLevelBase.h"

class BackGround;

class RoundA1Level : public RoundLevelBase
{
public:
	RoundA1Level();
	~RoundA1Level();

	RoundA1Level(const RoundA1Level& _Other) = delete;
	RoundA1Level(RoundA1Level&& _Other) noexcept = delete;
	RoundA1Level& operator=(const RoundA1Level& _Other) = delete;
	RoundA1Level& operator=(const RoundA1Level&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	void ResourceLoad();
	void CreateBackGround();
};

