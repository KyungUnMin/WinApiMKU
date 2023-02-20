#include "Monster_Dorabo.h"
#include <GameEngineCore/GameEngineRender.h>
#include "MonsterFSM.h"

std::vector<FrameAnimationParameter> Monster_Dorabo::AniParams;

class Dorabo_AniParamInit
{
public:
	Dorabo_AniParamInit();
	~Dorabo_AniParamInit() {}
};

Dorabo_AniParamInit Init_Dorabo = Dorabo_AniParamInit();

Dorabo_AniParamInit::Dorabo_AniParamInit()
{
	Monster_Dorabo::AniParams.resize(static_cast<int>(Dorabo_AniType::Count));

	//-------------------------------------------------------[HorizonFly]----------------------------------------------

	int StartIndex = 0;
	int IndexCount = 4;
	float InterTimer = 0.1f;
	bool Loop = true;

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Right_HorizonFly)] = FrameAnimationParameter
	{
		.AnimationName = "Right_HorizonFly",
		.ImageName = Monster_Dorabo::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Left_HorizonFly)] = FrameAnimationParameter
	{
		.AnimationName = "Left_HorizonFly",
		.ImageName = Monster_Dorabo::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Right_HorizonFly_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_HorizonFly_Rage",
		.ImageName = Monster_Dorabo::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Left_HorizonFly_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_HorizonFly_Rage",
		.ImageName = Monster_Dorabo::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//------------------------------------------------------------[Tired]-----------------------------------------

	StartIndex = 8;
	IndexCount = 3;
	InterTimer = 0.1f;
	Loop = true;

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Right_Tired)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Tired",
		.ImageName = Monster_Dorabo::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Left_Tired)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Tired",
		.ImageName = Monster_Dorabo::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};


	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Right_Tired_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Tired_Rage",
		.ImageName = Monster_Dorabo::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Left_Tired_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Tired_Rage",
		.ImageName = Monster_Dorabo::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//-----------------------------------------------------------[Falling]-----------------------------------------

	StartIndex = 11;
	IndexCount = 1;
	InterTimer = FLT_MAX;
	Loop = true;

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Right_Falling)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Falling",
		.ImageName = Monster_Dorabo::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Left_Falling)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Falling",
		.ImageName = Monster_Dorabo::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Right_Falling_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Falling_Rage",
		.ImageName = Monster_Dorabo::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Left_Falling_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Falling_Rage",
		.ImageName = Monster_Dorabo::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//------------------------------------------------------------[VerticalShake]-----------------------------------------

	StartIndex = 11;
	IndexCount = 1;
	InterTimer = FLT_MAX;
	Loop = true;

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Right_VerticalShake)] = FrameAnimationParameter
	{
		.AnimationName = "Right_VerticalShake",
		.ImageName = Monster_Dorabo::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Left_VerticalShake)] = FrameAnimationParameter
	{
		.AnimationName = "Left_VerticalShake",
		.ImageName = Monster_Dorabo::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Right_VerticalShake_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_VerticalShake_Rage",
		.ImageName = Monster_Dorabo::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Left_VerticalShake_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_VerticalShake_Rage",
		.ImageName = Monster_Dorabo::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//------------------------------------------------------------[Dizzy]-----------------------------------------

	StartIndex = 9;
	IndexCount = 1;
	InterTimer = FLT_MAX;
	Loop = true;

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Right_Dizzy)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Dizzy",
		.ImageName = Monster_Dorabo::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Left_Dizzy)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Dizzy",
		.ImageName = Monster_Dorabo::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};


	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Right_Dizzy_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Dizzy_Rage",
		.ImageName = Monster_Dorabo::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Left_Dizzy_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Dizzy_Rage",
		.ImageName = Monster_Dorabo::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//------------------------------------------------------------[RaiseFly]-----------------------------------------

	StartIndex = 4;
	IndexCount = 4;
	InterTimer = 0.1f;
	Loop = true;

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Right_Raise)] = FrameAnimationParameter
	{
		.AnimationName = "Right_RaiseFly",
		.ImageName = Monster_Dorabo::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Left_Raise)] = FrameAnimationParameter
	{
		.AnimationName = "Left_RaiseFly",
		.ImageName = Monster_Dorabo::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};


	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Right_Raise_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_RaiseFly_Rage",
		.ImageName = Monster_Dorabo::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Left_Raise_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_RaiseFly_Rage",
		.ImageName = Monster_Dorabo::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//---------------------------------------------------------------------[Lock]---------------------------------------

	StartIndex = 0;
	IndexCount = 3;
	InterTimer = 0.25f;

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Lock)] = FrameAnimationParameter
	{
		.AnimationName = "Lock",
		.ImageName = Monster_Dorabo::LockImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	StartIndex = 3;
	IndexCount = 3;

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Lock_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Lock_Rage",
		.ImageName = Monster_Dorabo::LockImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//---------------------------------------------------------------------[Dead]---------------------------------------

	StartIndex = 0;
	IndexCount = 4;
	InterTimer = 0.1f;

	Monster_Dorabo::AniParams[static_cast<int>(Dorabo_AniType::Dead)] = FrameAnimationParameter
	{
		.AnimationName = "Dead",
		.ImageName = Monster_Dorabo::DeadImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	
}
