#pragma once
#include "MonsterStateBase.h"



class MonsterState_Dead : public MonsterStateBase
{
public:
	MonsterState_Dead();
	~MonsterState_Dead();

	MonsterState_Dead(const MonsterState_Dead& _Other) = delete;
	MonsterState_Dead(MonsterState_Dead&& _Other) noexcept = delete;
	MonsterState_Dead& operator=(const MonsterState_Dead& _Other) = delete;
	MonsterState_Dead& operator=(const MonsterState_Dead&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;
	void ExitState() override;

private:
	const float4	AreaOffset		= float4{ 50.f,  50.f };
	float4				ScreenSize		= float4::Zero;

	float4				NowSpeed		= float4{ 1200.f, -1000.f };
	float4				GravityAcc		= float4{ 0.f, 400.f };

	void CreateItem();
};

