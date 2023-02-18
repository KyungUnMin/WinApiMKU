#pragma once
#include "MonsterStateBase.h"

class MonsterState_RocketDash : public MonsterStateBase
{
public:
	MonsterState_RocketDash();
	~MonsterState_RocketDash();

	MonsterState_RocketDash(const MonsterState_RocketDash& _Other) = delete;
	MonsterState_RocketDash(MonsterState_RocketDash&& _Other) noexcept = delete;
	MonsterState_RocketDash& operator=(const MonsterState_RocketDash& _Other) = delete;
	MonsterState_RocketDash& operator=(const MonsterState_RocketDash&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 DashSpeed = float4{ 500.f, 0.f };

};

