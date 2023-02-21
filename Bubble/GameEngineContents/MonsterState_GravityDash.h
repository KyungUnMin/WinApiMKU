#pragma once
#include "MonsterStateBase.h"

class MonsterState_GravityDash : public MonsterStateBase
{
public:
	MonsterState_GravityDash();
	~MonsterState_GravityDash();

	MonsterState_GravityDash(const MonsterState_GravityDash& _Other) = delete;
	MonsterState_GravityDash(MonsterState_GravityDash&& _Other) noexcept = delete;
	MonsterState_GravityDash& operator=(const MonsterState_GravityDash& _Other) = delete;
	MonsterState_GravityDash& operator=(const MonsterState_GravityDash&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime)  override;
	void EnterState() override;
	void ExitState() override;

private:
	const float4	DashGravity			= float4{ 0.f, 300.f };
	const float		ScreenOutOffsetY = 50.f;

	float4				DashSpeed				= { 500.f, 0.f };
	float				DashDuration			= 5.f;
	float				AccTime					= 0.f;
};

