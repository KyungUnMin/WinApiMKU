#pragma once
#include "MonsterMissleBase.h"

class RoundLevelBase;

class MonsterMissle_BossBeer : public MonsterMissleBase
{
public:
	static const std::string_view ImagePath;
	static const std::string_view ThrowAniName;
	static const std::string_view CrushAniName;

	static const std::string_view SFXName;

	MonsterMissle_BossBeer();
	~MonsterMissle_BossBeer() override;

	MonsterMissle_BossBeer(const MonsterMissle_BossBeer& _Other) = delete;
	MonsterMissle_BossBeer(MonsterMissle_BossBeer&& _Other) noexcept = delete;
	MonsterMissle_BossBeer& operator=(const MonsterMissle_BossBeer& _Other) = delete;
	MonsterMissle_BossBeer& operator=(const MonsterMissle_BossBeer&& _Other) noexcept = delete;

	void ThrowMissle(const float4& _Dir) override
	{
		MoveDir = _Dir;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	enum class State
	{
		Throw,
		Crush
	};

	State						CurState		= State::Throw;
	RoundLevelBase*	RoundLevel	= nullptr;
	float4						MoveDir		= float4::Zero;
	float						MoveSpeed	= 400.f;

	void ResourceLoad();
	void LoadSFX();
	void CreateAnimation();

	void ThrowMove(float _DeltaTime);
	void WaitingCrush();
};

