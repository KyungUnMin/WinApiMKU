#pragma once
#include "MonsterStateBase.h"

class MonsterState_VerticalShake : public MonsterStateBase
{
public:
	static const std::string_view AniName;

	MonsterState_VerticalShake();
	~MonsterState_VerticalShake() override;

	MonsterState_VerticalShake(const MonsterState_VerticalShake& _Other) = delete;
	MonsterState_VerticalShake(MonsterState_VerticalShake&& _Other) noexcept = delete;
	MonsterState_VerticalShake& operator=(const MonsterState_VerticalShake& _Other) = delete;
	MonsterState_VerticalShake& operator=(const MonsterState_VerticalShake&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	const float		ShakeLength		= 50.f;
	const size_t		ShakeCnt				= 3;
	const float		MoveDuration		= 0.1f;

	float4				OriginPos				= float4::Zero;
	float4				PivotPos				= float4::Zero;
	size_t				MoveCnt				= 0;

	float				AccTime				= 0.f;

	void Move(float _DeltaTime);
};

