#pragma once
#include "RoundLevelBase.h"

enum class RoundA3_RenderOrder
{
	BackGround,
	Obstacle,

};

class RoundA3Level : public RoundLevelBase
{
public:
	RoundA3Level();
	~RoundA3Level();

	RoundA3Level(const RoundA3Level& _Other) = delete;
	RoundA3Level(RoundA3Level&& _Other) noexcept = delete;
	RoundA3Level& operator=(const RoundA3Level& _Other) = delete;
	RoundA3Level& operator=(const RoundA3Level&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;


private:


	void ResourceLoad();
	void CreateBackGround();
};

