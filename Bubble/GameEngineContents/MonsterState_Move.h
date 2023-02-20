#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "MonsterStateBase.h"


class MonsterState_Move : public MonsterStateBase
{
public:
	MonsterState_Move();
	~MonsterState_Move() override;

	MonsterState_Move(const MonsterState_Move& _Other) = delete;
	MonsterState_Move(MonsterState_Move&& _Other) noexcept = delete;
	MonsterState_Move& operator=(const MonsterState_Move& _Other) = delete;
	MonsterState_Move& operator=(const MonsterState_Move&& _Other) noexcept = delete;

	inline const float4& GetSpeed()
	{
		return MoveSpeed;
	}

	inline void SetSpeed(const float4& _Speed)
	{
		MoveSpeed = _Speed;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	const float				PlayerFindRange		= 10.f;
	float4						MoveSpeed				= float4{ 150.f, 0.f };

	//점프하는 확률에 관한 값
	const int					CaseDoJump			= 50;

	bool IsPlayerPosOver();
	float HorizonSizeWithPlayer();
};

