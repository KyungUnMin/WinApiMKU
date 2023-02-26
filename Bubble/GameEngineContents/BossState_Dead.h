#pragma once
#include "BossStateBase.h"

class BossState_Dead : public BossStateBase
{
public:
	BossState_Dead();
	~BossState_Dead() override;

	BossState_Dead(const BossState_Dead& _Other) = delete;
	BossState_Dead(BossState_Dead&& _Other) noexcept = delete;
	BossState_Dead& operator=(const BossState_Dead& _Other) = delete;
	BossState_Dead& operator=(const BossState_Dead&& _Other) noexcept = delete;

protected:
	void EnterState() override;
	void Update(float _DeltaTime) override;

private:
	const float4 ScreenOutOffset	= float4{ 0.f, 300.f };
	const float4 StartSpeed				= float4{ 100.f, -200.f };
	const float	Gravity					= 200.f;

	float4 NowSpeed						= float4::Zero;
	float4 ScreenSize						= float4::Zero;

	void SelectDirection();
};

