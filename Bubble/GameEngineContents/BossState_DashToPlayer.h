#pragma once
#include "BossStateBase.h"
#include <GameEngineBase/GameEngineMath.h>

class BossState_DashToPlayer : public BossStateBase
{
public:
	BossState_DashToPlayer();
	~BossState_DashToPlayer() override;

	BossState_DashToPlayer(const BossState_DashToPlayer& _Other) = delete;
	BossState_DashToPlayer(BossState_DashToPlayer&& _Other) noexcept = delete;
	BossState_DashToPlayer& operator=(const BossState_DashToPlayer& _Other) = delete;
	BossState_DashToPlayer& operator=(const BossState_DashToPlayer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void EnterState() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime);

	virtual void Move(float _DeltaTime);

	inline const float4& GetDir()
	{
		return Dir;
	}

	bool IsScreenOutPos(const float4 _NextPos);
	void CalcDirection();

	inline const void SetDir(const float4& _Dir)
	{
		Dir = _Dir;
	}

private:
	CollisionData	MoveArea	= CollisionData();
	float4				Dir				= float4::Zero;

	HPEN				DebugPen	= HPEN();
	
	float				PrevTime		= 0.f;
	const float		CalcTerm		= 3.f;


	bool CheckDamaged();
};

