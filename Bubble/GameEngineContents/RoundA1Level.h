#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class RoundA1Level : public GameEngineLevel
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
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:

};

