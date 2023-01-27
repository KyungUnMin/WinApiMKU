#pragma once
#include "RoundLevelBase.h"


class RoundA2Level : public RoundLevelBase
{
public:
	RoundA2Level();
	~RoundA2Level();

	RoundA2Level(const RoundA2Level& _Other) = delete;
	RoundA2Level(RoundA2Level&& _Other) noexcept = delete;
	RoundA2Level& operator=(const RoundA2Level& _Other) = delete;
	RoundA2Level& operator=(const RoundA2Level&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:


	void ResourceLoad();
	void CreateBackGround();
};

