#pragma once
#include "MonsterStateBase.h"

class MonsterState_Tired : public MonsterStateBase
{
public:
	static const std::string_view AniName;

	MonsterState_Tired();
	~MonsterState_Tired();

	MonsterState_Tired(const MonsterState_Tired& _Other) = delete;
	MonsterState_Tired(MonsterState_Tired&& _Other) noexcept = delete;
	MonsterState_Tired& operator=(const MonsterState_Tired& _Other) = delete;
	MonsterState_Tired& operator=(const MonsterState_Tired&& _Other) noexcept = delete;



protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	const float		FallLowTime		= 3.f;
	const float		FallHighTime		= 5.f;

	float				FallChangeTime	= 0.f;
	float				AccTime				= 0.f;
};

