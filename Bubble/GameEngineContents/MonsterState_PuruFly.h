#pragma once
#include "MonsterStateBase.h"

class RoundLevelBase;

class MonsterState_PuruFly : public MonsterStateBase
{
public:
	static const std::string_view AniNames[2];

	MonsterState_PuruFly();
	~MonsterState_PuruFly() override;

	MonsterState_PuruFly(const MonsterState_PuruFly& _Other) = delete;
	MonsterState_PuruFly(MonsterState_PuruFly&& _Other) noexcept = delete;
	MonsterState_PuruFly& operator=(const MonsterState_PuruFly& _Other) = delete;
	MonsterState_PuruFly& operator=(const MonsterState_PuruFly&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	enum class MoveDir
	{
		Up,
		Down,
		Count
	};

	RoundLevelBase*	RoundLevel	= nullptr;
	MoveDir					CurState		= MoveDir::Up;
	const float4			MoveSpeed	= float4{ 100.f, 200.f };
	float4						NowDir			= float4{ 1.f, 1.f };

	
	void AnimationChange();
};

