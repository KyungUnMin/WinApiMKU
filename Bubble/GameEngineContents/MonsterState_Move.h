#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "MonsterStateBase.h"


class RoundLevelBase;

class MonsterState_Move : public MonsterStateBase
{
public:
	MonsterState_Move();
	~MonsterState_Move();

	MonsterState_Move(const MonsterState_Move& _Other) = delete;
	MonsterState_Move(MonsterState_Move&& _Other) noexcept = delete;
	MonsterState_Move& operator=(const MonsterState_Move& _Other) = delete;
	MonsterState_Move& operator=(const MonsterState_Move&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	const float4			MoveSpeed		= float4{ 150.f, 0.f };
	

	bool IsPlayerPosOver();
	float HorizonSizeWithPlayer();
};

