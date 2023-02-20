#pragma once
#include "MonsterBase.h"

class FrameAnimationParameter;

enum class Dorabo_AniType
{
	Right_HorizonFly,
	Left_HorizonFly,
	Right_HorizonFly_Rage,
	Left_HorizonFly_Rage,

	Right_Tired,
	Left_Tired,
	Right_Tired_Rage,
	Left_Tired_Rage,

	Right_Falling,
	Left_Falling,
	Right_Falling_Rage,
	Left_Falling_Rage,

	Right_VerticalShake,
	Left_VerticalShake,
	Right_VerticalShake_Rage,
	Left_VerticalShake_Rage,

	Right_Dizzy,
	Left_Dizzy,
	Right_Dizzy_Rage,
	Left_Dizzy_Rage,

	Right_Raise,
	Left_Raise,
	Right_Raise_Rage,
	Left_Raise_Rage,

	Lock,
	Lock_Rage,
	Dead,

	Count
};

class Monster_Dorabo : public MonsterBase
{
public:
	friend class Dorabo_AniParamInit;

	static const std::string_view		RightImagePath;
	static const std::string_view		LeftImagePath;
	static const std::string_view		RightRageImagePath;
	static const std::string_view		LeftRageImagePath;
	static const std::string_view		LockImagePath;
	static const std::string_view		DeadImagePath;

	Monster_Dorabo();
	~Monster_Dorabo() override;

	Monster_Dorabo(const Monster_Dorabo& _Other) = delete;
	Monster_Dorabo(Monster_Dorabo&& _Other) noexcept = delete;
	Monster_Dorabo& operator=(const Monster_Dorabo& _Other) = delete;
	Monster_Dorabo& operator=(const Monster_Dorabo&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	const float4 FallSpeed = float4{ 0.f, 600.f };

	void ResourceLoad();
	bool FallToShake(float _DeltaTime);

	static std::vector<FrameAnimationParameter> AniParams;
};

