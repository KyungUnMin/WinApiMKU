#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class RoundA2Level : public GameEngineLevel
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
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:

};

