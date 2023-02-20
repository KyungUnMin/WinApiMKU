#pragma once
#include "MonsterStateBase.h"

class MonsterState_Dizzy : public MonsterStateBase
{
public:
	static const std::string_view AniName;

	MonsterState_Dizzy();
	~MonsterState_Dizzy() override;

	MonsterState_Dizzy(const MonsterState_Dizzy& _Other) = delete;
	MonsterState_Dizzy(MonsterState_Dizzy&& _Other) noexcept = delete;
	MonsterState_Dizzy& operator=(const MonsterState_Dizzy& _Other) = delete;
	MonsterState_Dizzy& operator=(const MonsterState_Dizzy&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	const float		RaiseChangeTime	= 1.5f;
	const int			DirChangeCnt			= 5;

	float				AccTime					= 0.f;
	int					NowDirChangeCnt	= 0;

};

