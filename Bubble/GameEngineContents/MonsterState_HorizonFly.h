#pragma once
#include "MonsterStateBase.h"

class MonsterState_HorizonFly : public MonsterStateBase
{
public:
	static const std::string_view AniName;

	MonsterState_HorizonFly();
	~MonsterState_HorizonFly();

	MonsterState_HorizonFly(const MonsterState_HorizonFly& _Other) = delete;
	MonsterState_HorizonFly(MonsterState_HorizonFly&& _Other) noexcept = delete;
	MonsterState_HorizonFly& operator=(const MonsterState_HorizonFly& _Other) = delete;
	MonsterState_HorizonFly& operator=(const MonsterState_HorizonFly&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	const float4	MoveSpeed				= float4{ 100.f, 0.f };
	const float		TiredLowTime			= 3.f;
	const float		TiredHighTime			= 10.f;

	float				TiredChangeTime	= 0.f;
	float				AccTime					= 0.f;
};

