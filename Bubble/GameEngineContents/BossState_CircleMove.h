#pragma once
#include <Windows.h>
#include "BossStateBase.h"

class BossState_CircleMove : public BossStateBase
{
public:
	BossState_CircleMove();
	~BossState_CircleMove() override;

	BossState_CircleMove(const BossState_CircleMove& _Other) = delete;
	BossState_CircleMove(BossState_CircleMove&& _Other) noexcept = delete;
	BossState_CircleMove& operator=(const BossState_CircleMove& _Other) = delete;
	BossState_CircleMove& operator=(const BossState_CircleMove&& _Other) noexcept = delete;

protected:
	void Start() override;
	void EnterState() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	const float		Radius				= 150.f;
	float4				Pivot				= float4::Zero;
	float				RotateAngle	= 0.f;

	HPEN				DebugPen		= HPEN();


	void Update_Move(float _DeltaTime);
	void Update_CircleMove(float _DeltaTime, float _Distance);
	void Update_Direction();

	void Update_MoveToPivot(float _DeltaTime, float4 _Dir);
};

