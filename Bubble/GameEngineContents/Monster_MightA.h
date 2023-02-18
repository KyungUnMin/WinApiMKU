#pragma once
#include "MonsterBase.h"

class FrameAnimationParameter;

enum class MightA_AniType
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


class Monster_MightA : public MonsterBase
{
public:
	friend class MightA_AniParamInit;

	static const std::string_view		RightImagePath;
	static const std::string_view		LeftImagePath;
	static const std::string_view		RightRageImagePath;
	static const std::string_view		LeftRageImagePath;
	static const std::string_view		LockImagePath;
	static const std::string_view		DeadImagePath;

	Monster_MightA();
	~Monster_MightA() override;

	Monster_MightA(const Monster_MightA& _Other) = delete;
	Monster_MightA(Monster_MightA&& _Other) noexcept = delete;
	Monster_MightA& operator=(const Monster_MightA& _Other) = delete;
	Monster_MightA& operator=(const Monster_MightA&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

	void ResourceLoad();

	static std::vector<FrameAnimationParameter> AniParams;
};

