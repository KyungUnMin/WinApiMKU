#pragma once
#include "BossStateBase.h"
#include <GameEngineBase/GameEngineMath.h>

class BossState_DashToPlayer : public BossStateBase
{
public:
	BossState_DashToPlayer();
	~BossState_DashToPlayer();

	BossState_DashToPlayer(const BossState_DashToPlayer& _Other) = delete;
	BossState_DashToPlayer(BossState_DashToPlayer&& _Other) noexcept = delete;
	BossState_DashToPlayer& operator=(const BossState_DashToPlayer& _Other) = delete;
	BossState_DashToPlayer& operator=(const BossState_DashToPlayer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void EnterState() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime);

private:
	CollisionData	MoveArea	= CollisionData();
	float4				Dir				= float4::Zero;

	HPEN				DebugPen	= HPEN();

	void CalcDirection();
	bool CheckDamaged();
	void Move(float _DeltaTime);
	bool IsScreenOutPos(const float4 _NextPos);
};

