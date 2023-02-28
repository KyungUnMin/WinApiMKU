#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;

class BossDeadEffect : public GameEngineActor
{
public:
	BossDeadEffect();
	~BossDeadEffect() override;

	BossDeadEffect(const BossDeadEffect& _Other) = delete;
	BossDeadEffect(BossDeadEffect&& _Other) noexcept = delete;
	BossDeadEffect& operator=(const BossDeadEffect& _Other) = delete;
	BossDeadEffect& operator=(const BossDeadEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRender*	RenderPtr	= nullptr;
	const float					PosRadius	= 200.f;

	void SettingRender();
	void SettingPosition();
};

