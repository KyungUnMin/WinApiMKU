#pragma once
#include "PointEffect.h"

class BossDeadPoint : public PointEffect
{
public:
	BossDeadPoint();
	~BossDeadPoint() override;

	BossDeadPoint(const BossDeadPoint& _Other) = delete;
	BossDeadPoint(BossDeadPoint&& _Other) noexcept = delete;
	BossDeadPoint& operator=(const BossDeadPoint& _Other) = delete;
	BossDeadPoint& operator=(const BossDeadPoint&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	const int			KillPoint		= 100000;
	const float4	MoveSpeed	= float4{ 0.f, 150.f };
	const float4	MaxScale		= float4{ 400.f, 100.f };
};

