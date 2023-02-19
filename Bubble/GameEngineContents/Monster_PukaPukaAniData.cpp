#include "Monster_PukaPuka.h"
#include <string_view>
#include <GameEngineCore/GameEngineRender.h>
#include "MonsterFSM.h"

std::vector<FrameAnimationParameter> Monster_PukaPuka::AniParams;


class PukaPuka_AniParamInit
{
public:
	PukaPuka_AniParamInit();
	~PukaPuka_AniParamInit()
	{

	}
};

PukaPuka_AniParamInit Init_Puka = PukaPuka_AniParamInit();

PukaPuka_AniParamInit::PukaPuka_AniParamInit()
{
	Monster_PukaPuka::AniParams.resize(static_cast<int>(PukaPuka_AniType::Count));

	//-------------------------------------------------------[ReflectionFly]----------------------------------------------

	int StartIndex = 0;
	int IndexCount = 2;
	float InterTimer = 0.1f;
	bool Loop = true;

	Monster_PukaPuka::AniParams[static_cast<int>(PukaPuka_AniType::Right_ReflectionFly)] = FrameAnimationParameter
	{
		.AnimationName = "Right_ReflectionFly",
		.ImageName = Monster_PukaPuka::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_PukaPuka::AniParams[static_cast<int>(PukaPuka_AniType::Left_ReflectionFly)] = FrameAnimationParameter
	{
		.AnimationName = "Left_ReflectionFly",
		.ImageName = Monster_PukaPuka::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_PukaPuka::AniParams[static_cast<int>(PukaPuka_AniType::Right_ReflectionFly_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_ReflectionFly_Rage",
		.ImageName = Monster_PukaPuka::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_PukaPuka::AniParams[static_cast<int>(PukaPuka_AniType::Left_ReflectionFly_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_ReflectionFly_Rage",
		.ImageName = Monster_PukaPuka::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//---------------------------------------------------------------------[Lock]---------------------------------------

	StartIndex = 0;
	IndexCount = 3;
	InterTimer = 0.25f;

	Monster_PukaPuka::AniParams[static_cast<int>(PukaPuka_AniType::Lock)] = FrameAnimationParameter
	{
		.AnimationName = "Lock",
		.ImageName = Monster_PukaPuka::LockImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	StartIndex = 3;
	IndexCount = 3;

	Monster_PukaPuka::AniParams[static_cast<int>(PukaPuka_AniType::Lock_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Lock_Rage",
		.ImageName = Monster_PukaPuka::LockImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//---------------------------------------------------------------------[Dead]---------------------------------------

	StartIndex = 0;
	IndexCount = 4;
	InterTimer = 0.1f;

	Monster_PukaPuka::AniParams[static_cast<int>(PukaPuka_AniType::Dead)] = FrameAnimationParameter
	{
		.AnimationName = "Dead",
		.ImageName = Monster_PukaPuka::DeadImagePath,
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
		Monster_PukaPuka::AniParams.push_back
		({
			.AnimationName = FallingAniNames[i],
			.ImageName = Monster_PukaPuka::RightImagePath,
			.Start = 0,
			.End = 0,
			.InterTimer = 0.f,
			.Loop = false
			});
	}

}