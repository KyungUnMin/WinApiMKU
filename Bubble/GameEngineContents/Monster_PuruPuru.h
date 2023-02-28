#pragma once
#include "MonsterBase.h"

enum class PuruPuru_AniType
{
	FlyUp,
	FlyDown,

	Lock,
	Lock_Rage,
	Dead,

	Count
};

class FrameAnimationParameter;

class Monster_PuruPuru : public MonsterBase
{
public:
	friend class PuruPuru_AniParamInit;

	static const std::string_view		ImagePath;
	static const std::string_view		LockImagePath;
	static const std::string_view		DeadImagePath;

	Monster_PuruPuru();
	~Monster_PuruPuru();

	Monster_PuruPuru(const Monster_PuruPuru& _Other) = delete;
	Monster_PuruPuru(Monster_PuruPuru&& _Other) noexcept = delete;
	Monster_PuruPuru& operator=(const Monster_PuruPuru& _Other) = delete;
	Monster_PuruPuru& operator=(const Monster_PuruPuru&& _Other) noexcept = delete;

protected:
	void Start() override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override
	{
		IsAlreadyFall = false;
	}

private:
	bool IsAlreadyFall = false;

	void ResourceLoad();
	bool FallingToFly(float _DeltaTime);

	static std::vector<FrameAnimationParameter> AniParams;
};

