#pragma once
#include "MonsterStateBase.h"

class RoundLevelBase;

class MonsterState_ReflectionFly : public MonsterStateBase
{
public:
	MonsterState_ReflectionFly();
	~MonsterState_ReflectionFly();

	MonsterState_ReflectionFly(const MonsterState_ReflectionFly& _Other) = delete;
	MonsterState_ReflectionFly(MonsterState_ReflectionFly&& _Other) noexcept = delete;
	MonsterState_ReflectionFly& operator=(const MonsterState_ReflectionFly& _Other) = delete;
	MonsterState_ReflectionFly& operator=(const MonsterState_ReflectionFly&& _Other) noexcept = delete;

	void SetReflectionDir(bool _IsClockWise)
	{
		if (true == _IsClockWise)
			Angle = -abs(Angle);
		else
			Angle = abs(Angle);
	}

	inline void SetReflectionAngle(float _Degree)
	{
		Angle = _Degree;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	RoundLevelBase*	RoundLevel		= nullptr;
	float4						MoveDir			= float4{ 8.f, -2.f };
	const float4			RotateRange	= float4{ 100.f, 100.f };

	const float				MoveSpeed		= 75.f;

	float						Angle = 14.f;


	void Move(float _DeltaTime);
};

