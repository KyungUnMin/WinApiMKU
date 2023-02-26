#pragma once
#include "BossStateBase.h"

class GameEngineRender;

class BossState_Lock : public BossStateBase
{
public:
	static const std::string_view BubbleLockAniName;


	BossState_Lock();
	~BossState_Lock() override;

	BossState_Lock(const BossState_Lock& _Other) = delete;
	BossState_Lock(BossState_Lock&& _Other) noexcept = delete;
	BossState_Lock& operator=(const BossState_Lock& _Other) = delete;
	BossState_Lock& operator=(const BossState_Lock&& _Other) noexcept = delete;

protected:
	void Start() override;
	void EnterState() override;
	void Update(float _DeltaTime) override;
	void ExitState() override;

private:
	GameEngineRender*	LockBubble		= nullptr;

	float4							StartPos			= float4::Zero;
	float4							DestPos			= float4::Zero;

	const float					MoveSpeed		= 200.f;
	const float					LockTime			= 10.f;
	float							AccTime			= 0.f;

	void Move();
};

