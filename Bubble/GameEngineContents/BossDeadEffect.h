#pragma once
#include "PointEffect.h"

class BossDeadEffect : public PointEffect
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
	const int			KillPoint		= 100000;
	const float4	MoveSpeed	= float4{ 0.f, 150.f };
	const float4	MaxScale		= float4{ 400.f, 100.f };

	void SettingPointEffect();
	void CreatePopEffect();
};

