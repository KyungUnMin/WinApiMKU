#pragma once
#include <vector>
#include <string_view>
#include "MonsterBase.h"

class FrameAnimationParameter;

enum class ZenChan_AniType
{
	Right_Move,
	Left_Move,
	Right_Move_Rage,
	Left_Move_Rage,

	Right_Falling,
	Left_Falling,
	Right_Falling_Rage,
	Left_Falling_Rage,

	Right_Jump,
	Left_Jump,
	Right_Jump_Rage,
	Left_Jump_Rage,

	Lock,
	Lock_Rage,
	Dead,

	Count
};

class Monster_ZenChan : public MonsterBase
{
public:
	friend class ZenChan_AniParamInit;

	static const std::string_view		RightImagePath;
	static const std::string_view		LeftImagePath;
	static const std::string_view		RightRageImagePath;
	static const std::string_view		LeftRageImagePath;
	static const std::string_view		LockImagePath;
	static const std::string_view		DeadImagePath;

	Monster_ZenChan();
	~Monster_ZenChan() override;

	Monster_ZenChan(const Monster_ZenChan& _Other) = delete;
	Monster_ZenChan(Monster_ZenChan&& _Other) noexcept = delete;
	Monster_ZenChan& operator=(const Monster_ZenChan& _Other) = delete;
	Monster_ZenChan& operator=(const Monster_ZenChan&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	bool Test()
	{
		int a = 0;

		return false;
	}


	void ResourceLoad();

	static std::vector<FrameAnimationParameter> AniParams;
};

