#pragma once
#include "BossState_DashToPlayer.h"

class BossState_InfiniteDash : public BossState_DashToPlayer
{
public:
	BossState_InfiniteDash();
	~BossState_InfiniteDash() override;

	BossState_InfiniteDash(const BossState_InfiniteDash& _Other) = delete;
	BossState_InfiniteDash(BossState_InfiniteDash&& _Other) noexcept = delete;
	BossState_InfiniteDash& operator=(const BossState_InfiniteDash& _Other) = delete;
	BossState_InfiniteDash& operator=(const BossState_InfiniteDash&& _Other) noexcept = delete;

	void Move(float _DeltaTime) override;

protected:
	void EnterState() override;
	void Update(float _DeltaTime) override;

private:
	const float	ChangeStateTime	= 5.f;
	float			Timer						= 0.f;

	void CalcCenterDir();
};

