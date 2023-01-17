#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class RoundA_Enter : public GameEngineLevel
{
public:
	RoundA_Enter();
	~RoundA_Enter();

	RoundA_Enter(const RoundA_Enter& _Other) = delete;
	RoundA_Enter(RoundA_Enter&& _Other) noexcept = delete;
	RoundA_Enter& operator=(const RoundA_Enter& _Other) = delete;
	RoundA_Enter& operator=(const RoundA_Enter&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;


private:

};

