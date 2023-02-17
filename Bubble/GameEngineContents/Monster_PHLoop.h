#pragma once
#include "MonsterBase.h"

class FrameAnimationParameter;

enum class PHLoop_AniType
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


	Count
};

class Monster_PHLoop : public MonsterBase
{
public:
	friend class PHLoop_AniParamInit;

	static const std::string_view		RightImagePath;
	static const std::string_view		LeftImagePath;
	static const std::string_view		RightRageImagePath;
	static const std::string_view		LeftRageImagePath;
	static const std::string_view		LockImagePath;
	static const std::string_view		DeadImagePath;

	Monster_PHLoop();
	~Monster_PHLoop() override;

	Monster_PHLoop(const Monster_PHLoop& _Other) = delete;
	Monster_PHLoop(Monster_PHLoop&& _Other) noexcept = delete;
	Monster_PHLoop& operator=(const Monster_PHLoop& _Other) = delete;
	Monster_PHLoop& operator=(const Monster_PHLoop&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

	void ResourceLoad();
	bool MoveToDash(float _DeltaTime);

	static std::vector<FrameAnimationParameter> AniParams;
};

