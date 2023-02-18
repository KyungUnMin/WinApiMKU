#pragma once
#include "MonsterBase.h"

class FrameAnimationParameter;

enum class Warurin_AniType
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

	Right_ThrowMissle,
	Left_ThrowMissle,
	Right_ThrowMissle_Rage,
	Left_ThrowMissle_Rage,

	Count
};

class Monster_Warurin : public MonsterBase
{
public:
	friend class Warurin_AniParamInit;

	static const std::string_view		RightImagePath;
	static const std::string_view		LeftImagePath;
	static const std::string_view		RightRageImagePath;
	static const std::string_view		LeftRageImagePath;
	static const std::string_view		LockImagePath;
	static const std::string_view		DeadImagePath;

	Monster_Warurin();
	~Monster_Warurin();

	Monster_Warurin(const Monster_Warurin& _Other) = delete;
	Monster_Warurin(Monster_Warurin&& _Other) noexcept = delete;
	Monster_Warurin& operator=(const Monster_Warurin& _Other) = delete;
	Monster_Warurin& operator=(const Monster_Warurin&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	void ResourceLoad();
	bool MoveToThrow(float _DeltaTime);

	static std::vector<FrameAnimationParameter> AniParams;
};

