#pragma once
#include "MonsterStateBase.h"

class MonsterState_RaiseFly : public MonsterStateBase
{
public:
	static const std::string_view AniName;

	MonsterState_RaiseFly();
	~MonsterState_RaiseFly() override;

	MonsterState_RaiseFly(const MonsterState_RaiseFly& _Other) = delete;
	MonsterState_RaiseFly(MonsterState_RaiseFly&& _Other) noexcept = delete;
	MonsterState_RaiseFly& operator=(const MonsterState_RaiseFly& _Other) = delete;
	MonsterState_RaiseFly& operator=(const MonsterState_RaiseFly&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	const float4	OriginSpeed	= float4{ 0.f, 200.f };
	
	const int			BoostCnt			= 4;
	int					NowBoost		= 0;

	const float		BoostTime		= 0.5f;
	float				MoveTimer		= 0.f;
};

