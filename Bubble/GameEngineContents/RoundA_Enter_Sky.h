#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;

class RoundA_Enter_Sky : public GameEngineActor
{
public:
	RoundA_Enter_Sky();
	~RoundA_Enter_Sky();

	RoundA_Enter_Sky(const RoundA_Enter_Sky& _Other) = delete;
	RoundA_Enter_Sky(RoundA_Enter_Sky&& _Other) noexcept = delete;
	RoundA_Enter_Sky& operator=(const RoundA_Enter_Sky& _Other) = delete;
	RoundA_Enter_Sky& operator=(const RoundA_Enter_Sky&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRender*	SkyRender	= nullptr;
	float							PivotX			= 0.f;
	float							Range			= 0.f;
	float							MoveSpeed	= 10.f;
	int								Dir				= -1;
};

