#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "MonsterStateBase.h"


class MonsterState_Falling : public MonsterStateBase
{
public:
	static const std::string_view AniName;

	MonsterState_Falling();
	~MonsterState_Falling() override;

	MonsterState_Falling(const MonsterState_Falling& _Other) = delete;
	MonsterState_Falling(MonsterState_Falling&& _Other) noexcept = delete;
	MonsterState_Falling& operator=(const MonsterState_Falling& _Other) = delete;
	MonsterState_Falling& operator=(const MonsterState_Falling&& _Other) noexcept = delete;

	inline void SetGravitySpeed(const float4& _GravitySpeed)
	{
		GravitySpeed = _GravitySpeed;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	const float		ScreenOutOffsetY		= 50.f;
	float4				GravitySpeed				= float4{ 0.f, 200.f };
	bool					IsBlocked					= false;

	void Move(float _DeltaTime);
	bool CheckStateChange(float _DeltaTime);
};

