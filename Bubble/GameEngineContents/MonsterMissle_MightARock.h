#pragma once
#include "MonsterMissleBase.h"

class MonsterMissle_MightARock : public MonsterMissleBase
{
public:
	static const std::string AniNames[3];

	MonsterMissle_MightARock();
	~MonsterMissle_MightARock();

	MonsterMissle_MightARock(const MonsterMissle_MightARock& _Other) = delete;
	MonsterMissle_MightARock(MonsterMissle_MightARock&& _Other) noexcept = delete;
	MonsterMissle_MightARock& operator=(const MonsterMissle_MightARock& _Other) = delete;
	MonsterMissle_MightARock& operator=(const MonsterMissle_MightARock&& _Other) noexcept = delete;

	void ThrowMissle(const float4& _Dir) override;

protected:
	void Start() override;
	void Update(float _DeltaTime)  override;

private:
	enum class MR_State
	{
		Gather,
		Throw,
		Crack
	};

	MR_State		CurState			= MR_State::Gather;
	const float	MoveSpeed		= 500.f;

	void ResourceLoad();

	const std::string_view ImagePath = "MightARock.bmp";
};

