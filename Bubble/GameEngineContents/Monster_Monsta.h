#pragma once
#include "MonsterBase.h"

enum class Monsta_AniType
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

class Monster_Monsta : public MonsterBase
{
public:
	friend class Monsta_AniParamInit;

	static const std::string_view		RightImagePath;
	static const std::string_view		LeftImagePath;
	static const std::string_view		RightRageImagePath;
	static const std::string_view		LeftRageImagePath;
	static const std::string_view		LockImagePath;
	static const std::string_view		DeadImagePath;

	Monster_Monsta();
	~Monster_Monsta();

	Monster_Monsta(const Monster_Monsta& _Other) = delete;
	Monster_Monsta(Monster_Monsta&& _Other) noexcept = delete;
	Monster_Monsta& operator=(const Monster_Monsta& _Other) = delete;
	Monster_Monsta& operator=(const Monster_Monsta&& _Other) noexcept = delete;

	void Init(const float4& _StartDir, bool _IsClockWise);

protected:
	void Start() override;

private:
	const float	ReflectionAngle	= 70.f;
	const float	MoveSpeed			= 300.f;

	void ResourceLoad();
	bool FallingToFly(float _DeltaTime);

	static std::vector<FrameAnimationParameter> AniParams;
};

