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

	Right_VerticalShake,
	Left_VerticalShake,
	Right_VerticalShake_Rage,
	Left_VerticalShake_Rage,

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

class Monster_Dorabo : public MonsterBase
{
public:
	Monster_Dorabo();
	~Monster_Dorabo();

	Monster_Dorabo(const Monster_Dorabo& _Other) = delete;
	Monster_Dorabo(Monster_Dorabo&& _Other) noexcept = delete;
	Monster_Dorabo& operator=(const Monster_Dorabo& _Other) = delete;
	Monster_Dorabo& operator=(const Monster_Dorabo&& _Other) noexcept = delete;

protected:

private:

};

