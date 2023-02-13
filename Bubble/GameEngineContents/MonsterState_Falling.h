#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "MonsterStateBase.h"


class MonsterState_Falling : public MonsterStateBase
{
public:
	MonsterState_Falling();
	~MonsterState_Falling() override;

	MonsterState_Falling(const MonsterState_Falling& _Other) = delete;
	MonsterState_Falling(MonsterState_Falling&& _Other) noexcept = delete;
	MonsterState_Falling& operator=(const MonsterState_Falling& _Other) = delete;
	MonsterState_Falling& operator=(const MonsterState_Falling&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	const float4	GravitySpeed	= float4{ 0.f, 200.f };

	bool					IsBlocked		= false;


	bool CheckStateChange(float _DeltaTime);
};

