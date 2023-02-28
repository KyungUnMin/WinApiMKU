#pragma once
#include "MonsterBase.h"


enum class PukaPuka_AniType
{
	Right_ReflectionFly,
	Left_ReflectionFly,
	Right_ReflectionFly_Rage,
	Left_ReflectionFly_Rage,

	Lock,
	Lock_Rage,
	Dead,

	Count
};

class FrameAnimationParameter;

class Monster_PukaPuka : public MonsterBase
{
public:
	friend class PukaPuka_AniParamInit;

	static const std::string_view		RightImagePath;
	static const std::string_view		LeftImagePath;
	static const std::string_view		RightRageImagePath;
	static const std::string_view		LeftRageImagePath;
	static const std::string_view		LockImagePath;
	static const std::string_view		DeadImagePath;

	Monster_PukaPuka();
	~Monster_PukaPuka();

	Monster_PukaPuka(const Monster_PukaPuka& _Other) = delete;
	Monster_PukaPuka(Monster_PukaPuka&& _Other) noexcept = delete;
	Monster_PukaPuka& operator=(const Monster_PukaPuka& _Other) = delete;
	Monster_PukaPuka& operator=(const Monster_PukaPuka&& _Other) noexcept = delete;

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

