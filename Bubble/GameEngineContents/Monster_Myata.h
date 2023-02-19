#pragma once
#include "MonsterBase.h"

class FrameAnimationParameter;

enum class Myata_AniType
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

	Right_Dash,
	Left_Dash,
	Right_Dash_Rage,
	Left_Dash_Rage,

	Right_DashReady,
	Left_DashReady,
	Right_DashReady_Rage,
	Left_DashReady_Rage,

	Count
};

class Monster_Myata : public MonsterBase
{
public:
	friend class Myata_AniParamInit;

	static const std::string_view		RightImagePath;
	static const std::string_view		LeftImagePath;
	static const std::string_view		RightRageImagePath;
	static const std::string_view		LeftRageImagePath;
	static const std::string_view		LockImagePath;
	static const std::string_view		DeadImagePath;

	Monster_Myata();
	~Monster_Myata() override;

	Monster_Myata(const Monster_Myata& _Other) = delete;
	Monster_Myata(Monster_Myata&& _Other) noexcept = delete;
	Monster_Myata& operator=(const Monster_Myata& _Other) = delete;
	Monster_Myata& operator=(const Monster_Myata&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	const size_t DashReadyFrameIndex = 8;

	void ResourceLoad();
	bool MoveToDash(float _DeltaTime);

	static std::vector<FrameAnimationParameter> AniParams;
};

