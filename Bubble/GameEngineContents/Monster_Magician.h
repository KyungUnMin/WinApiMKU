#pragma once
#include "MonsterBase.h"

class FrameAnimationParameter;

enum class Magician_AniType
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

	Right_RocketDash,
	Left_RocketDash,
	Right_RocketDash_Rage,
	Left_RocketDash_Rage,

	Count
};

class Monster_Magician : public MonsterBase
{
public:
	friend class Magician_AniParamInit;

	static const std::string_view		RightImagePath;
	static const std::string_view		LeftImagePath;
	static const std::string_view		RightRageImagePath;
	static const std::string_view		LeftRageImagePath;
	static const std::string_view		LockImagePath;
	static const std::string_view		DeadImagePath;

	Monster_Magician();
	~Monster_Magician();

	Monster_Magician(const Monster_Magician& _Other) = delete;
	Monster_Magician(Monster_Magician&& _Other) noexcept = delete;
	Monster_Magician& operator=(const Monster_Magician& _Other) = delete;
	Monster_Magician& operator=(const Monster_Magician&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	const int RocketDashProbability = 20;

	void ResourceLoad();
	bool MagicianMoveStep(float _DeltaTime);
	

	static std::vector<FrameAnimationParameter> AniParams;
};

