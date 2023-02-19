#pragma once
#include "MonsterStateBase.h"

class MonsterState_RigidDash : public MonsterStateBase
{
public:
	static const std::string_view ReadyAniName;
	static const std::string_view DashAniName;

	MonsterState_RigidDash();
	~MonsterState_RigidDash() override;

	MonsterState_RigidDash(const MonsterState_RigidDash& _Other) = delete;
	MonsterState_RigidDash(MonsterState_RigidDash&& _Other) noexcept = delete;
	MonsterState_RigidDash& operator=(const MonsterState_RigidDash& _Other) = delete;
	MonsterState_RigidDash& operator=(const MonsterState_RigidDash&& _Other) noexcept = delete;

protected:
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	enum class State
	{
		Ready,
		Dash
	};

	State				NowState					= State::Ready;

	const float4	StartSpeed				= float4{ 600.f, 0.f };
	float				MoveAccTime			= 0.f;
	const float		MoveDuration			= 1.f;


	void Movement(float _DeltaTime);
	void Dash(float _DeltaTime);
};

