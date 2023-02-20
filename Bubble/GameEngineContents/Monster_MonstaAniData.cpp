#include "Monster_Monsta.h"
#include <string_view>
#include <GameEngineCore/GameEngineRender.h>
#include "MonsterFSM.h"

std::vector<FrameAnimationParameter> Monster_Monsta::AniParams;


class Monsta_AniParamInit
{
public:
	Monsta_AniParamInit();
	~Monsta_AniParamInit()
	{

	}
};

Monsta_AniParamInit Init_Monsta = Monsta_AniParamInit();

Monsta_AniParamInit::Monsta_AniParamInit()
{
	Monster_Monsta::AniParams.resize(static_cast<int>(Monsta_AniType::Count));

	//-------------------------------------------------------[ReflectionFly]----------------------------------------------

	int StartIndex = 0;
	int IndexCount = 4;
	float InterTimer = 0.1f;
	bool Loop = true;

	Monster_Monsta::AniParams[static_cast<int>(Monsta_AniType::Right_ReflectionFly)] = FrameAnimationParameter
	{
		.AnimationName = "Right_ReflectionFly",
		.ImageName = Monster_Monsta::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Monsta::AniParams[static_cast<int>(Monsta_AniType::Left_ReflectionFly)] = FrameAnimationParameter
	{
		.AnimationName = "Left_ReflectionFly",
		.ImageName = Monster_Monsta::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Monsta::AniParams[static_cast<int>(Monsta_AniType::Right_ReflectionFly_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_ReflectionFly_Rage",
		.ImageName = Monster_Monsta::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Monsta::AniParams[static_cast<int>(Monsta_AniType::Left_ReflectionFly_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_ReflectionFly_Rage",
		.ImageName = Monster_Monsta::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//---------------------------------------------------------------------[Lock]---------------------------------------

	StartIndex = 0;
	IndexCount = 3;
	InterTimer = 0.25f;

	Monster_Monsta::AniParams[static_cast<int>(Monsta_AniType::Lock)] = FrameAnimationParameter
	{
		.AnimationName = "Lock",
		.ImageName = Monster_Monsta::LockImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	StartIndex = 3;
	IndexCount = 3;

	Monster_Monsta::AniParams[static_cast<int>(Monsta_AniType::Lock_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Lock_Rage",
		.ImageName = Monster_Monsta::LockImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//---------------------------------------------------------------------[Dead]---------------------------------------

	StartIndex = 0;
	IndexCount = 4;
	InterTimer = 0.1f;

	Monster_Monsta::AniParams[static_cast<int>(Monsta_AniType::Dead)] = FrameAnimationParameter
	{
		.AnimationName = "Dead",
		.ImageName = Monster_Monsta::DeadImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//-----------------------------------------------------------[Falling]-----------------------------------------
	//Falling은 사용하지 않는 상태값, MonsterFSM 구조상 넣은 애니메이션

	const std::string_view FallingAniNames[4] =
	{
		"Right_Falling",
		"Left_Falling",
		"Right_Falling_Rage",
		"Left_Falling_Rage"
	};

	for (size_t i = 0; i < 4; ++i)
	{
		Monster_Monsta::AniParams.push_back
		({
			.AnimationName = FallingAniNames[i],
			.ImageName = Monster_Monsta::RightImagePath,
			.Start = 0,
			.End = 0,
			.InterTimer = 0.f,
			.Loop = false
		});
	}

}