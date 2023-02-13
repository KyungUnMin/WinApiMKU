#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "MonsterStateBase.h"

class MonsterState_Jump : public MonsterStateBase
{
public:
	MonsterState_Jump();
	~MonsterState_Jump();

	MonsterState_Jump(const MonsterState_Jump& _Other) = delete;
	MonsterState_Jump(MonsterState_Jump&& _Other) noexcept = delete;
	MonsterState_Jump& operator=(const MonsterState_Jump& _Other) = delete;
	MonsterState_Jump& operator=(const MonsterState_Jump&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;


private:
	float								AccTime					= 0.0f;
	const float						FallingChangeTime	= 0.5f;

	const float4					AirMoveSpeed			= float4{ 250.f, 0.f };
	const float4					JumpSpeed				= float4{ 100.f, 600.f };
	const float						ScreenTopOffset	= 50.f;

	bool CheckStateChange(float _DeltaTime);
	bool Movement(float _DeltaTime);
};

