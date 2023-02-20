#include "Monster_PuruPuru.h"
#include <GameEngineCore/GameEngineRender.h>
#include "MonsterFSM.h"

std::vector<FrameAnimationParameter> Monster_PuruPuru::AniParams;


class PuruPuru_AniParamInit
{
public:
	PuruPuru_AniParamInit();
	~PuruPuru_AniParamInit()
	{

	}
};

PuruPuru_AniParamInit Init_Puru = PuruPuru_AniParamInit();

PuruPuru_AniParamInit::PuruPuru_AniParamInit()
{
	Monster_PuruPuru::AniParams.resize(static_cast<int>(PuruPuru_AniType::Count));

	//-------------------------------------------------------[ReflectionFly]----------------------------------------------

	int StartIndex = 8;
	int IndexCount = 8;
	float InterTimer = 0.1f;
	bool Loop = true;

	Monster_PuruPuru::AniParams[static_cast<int>(PuruPuru_AniType::FlyUp)] = FrameAnimationParameter
	{
		.AnimationName = "UpFly",
		.ImageName = Monster_PuruPuru::ImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	StartIndex = 0;
	IndexCount = 8;
	InterTimer = 0.1f;
	Loop = true;

	Monster_PuruPuru::AniParams[static_cast<int>(PuruPuru_AniType::FlyDown)] = FrameAnimationParameter
	{
		.AnimationName = "DownFly",
		.ImageName = Monster_PuruPuru::ImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};



	//---------------------------------------------------------------------[Lock]---------------------------------------

	StartIndex = 0;
	IndexCount = 3;
	InterTimer = 0.25f;

	Monster_PuruPuru::AniParams[static_cast<int>(PuruPuru_AniType::Lock)] = FrameAnimationParameter
	{
		.AnimationName = "Lock",
		.ImageName = Monster_PuruPuru::LockImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	StartIndex = 3;
	IndexCount = 3;

	Monster_PuruPuru::AniParams[static_cast<int>(PuruPuru_AniType::Lock_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Lock_Rage",
		.ImageName = Monster_PuruPuru::LockImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//---------------------------------------------------------------------[Dead]---------------------------------------

	StartIndex = 0;
	IndexCount = 4;
	InterTimer = 0.1f;

	Monster_PuruPuru::AniParams[static_cast<int>(PuruPuru_AniType::Dead)] = FrameAnimationParameter
	{
		.AnimationName = "Dead",
		.ImageName = Monster_PuruPuru::DeadImagePath,
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
		Monster_PuruPuru::AniParams.push_back
		({
			.AnimationName = FallingAniNames[i],
			.ImageName = Monster_PuruPuru::ImagePath,
			.Start = 0,
			.End = 0,
			.InterTimer = 0.f,
			.Loop = false
		});
	}

}