#pragma once
#include "RoundLevelBase.h"

enum class RoundA1_RenderOrder
{
	BackGround,
	Obstacle,
};

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
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override{}
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override{}

private:
	void ResourceLoad();
	void CreateBackGround();
};

