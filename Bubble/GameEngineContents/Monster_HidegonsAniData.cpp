#include "Monster_Hidegons.h"
#include <GameEngineCore/GameEngineRender.h>
#include "MonsterFSM.h"

std::vector<FrameAnimationParameter> Monster_Hidegons::AniParams;

class Hidegons_AniParamInit
{
public:
	Hidegons_AniParamInit();
	~Hidegons_AniParamInit()
	{

	}
};

Hidegons_AniParamInit Init_Hidegons = Hidegons_AniParamInit();

Hidegons_AniParamInit::Hidegons_AniParamInit()
{
	Monster_Hidegons::AniParams.resize(static_cast<int>(Hidegons_AniType::Count));

	//-------------------------------------------------------[Move]----------------------------------------------

	int StartIndex = 0;
	int IndexCount = 4;
	float InterTimer = 0.1f;
	bool Loop = true;

	Monster_Hidegons::AniParams[static_cast<int>(Hidegons_AniType::Right_Move)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Move",
		.ImageName = Monster_Hidegons::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Hidegons::AniParams[static_cast<int>(Hidegons_AniType::Left_Move)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Move",
		.ImageName = Monster_Hidegons::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Hidegons::AniParams[static_cast<int>(Hidegons_AniType::Right_Move_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Move_Rage",
		.ImageName = Monster_Hidegons::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Hidegons::AniParams[static_cast<int>(Hidegons_AniType::Left_Move_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Move_Rage",
		.ImageName = Monster_Hidegons::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//-----------------------------------------------------------[Falling]-----------------------------------------

	StartIndex = 6;
	IndexCount = 2;

	Monster_Hidegons::AniParams[static_cast<int>(Hidegons_AniType::Right_Falling)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Falling",
		.ImageName = Monster_Hidegons::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Hidegons::AniParams[static_cast<int>(Hidegons_AniType::Left_Falling)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Falling",
		.ImageName = Monster_Hidegons::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Hidegons::AniParams[static_cast<int>(Hidegons_AniType::Right_Falling_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Falling_Rage",
		.ImageName = Monster_Hidegons::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Hidegons::AniParams[static_cast<int>(Hidegons_AniType::Left_Falling_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Falling_Rage",
		.ImageName = Monster_Hidegons::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//------------------------------------------------------------[Jump]-----------------------------------------

	StartIndex = 4;
	IndexCount = 2;

	Monster_Hidegons::AniParams[static_cast<int>(Hidegons_AniType::Right_Jump)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Jump",
		.ImageName = Monster_Hidegons::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Hidegons::AniParams[static_cast<int>(Hidegons_AniType::Left_Jump)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Jump",
		.ImageName = Monster_Hidegons::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};


	Monster_Hidegons::AniParams[static_cast<int>(Hidegons_AniType::Right_Jump_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Jump_Rage",
		.ImageName = Monster_Hidegons::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Hidegons::AniParams[static_cast<int>(Hidegons_AniType::Left_Jump_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Jump_Rage",
		.ImageName = Monster_Hidegons::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//---------------------------------------------------------------------[Lock]---------------------------------------

	StartIndex = 0;
	IndexCount = 3;
	InterTimer = 0.25f;

	Monster_Hidegons::AniParams[static_cast<int>(Hidegons_AniType::Lock)] = FrameAnimationParameter
	{
		.AnimationName = "Lock",
		.ImageName = Monster_Hidegons::LockImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	StartIndex = 3;
	IndexCount = 3;

	Monster_Hidegons::AniParams[static_cast<int>(Hidegons_AniType::Lock_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Lock_Rage",
		.ImageName = Monster_Hidegons::LockImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//---------------------------------------------------------------------[Dead]---------------------------------------

	StartIndex = 0;
	IndexCount = 4;
	InterTimer = 0.1f;

	Monster_Hidegons::AniParams[static_cast<int>(Hidegons_AniType::Dead)] = FrameAnimationParameter
	{
		.AnimationName = "Dead",
		.ImageName = Monster_Hidegons::DeadImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//---------------------------------------------------------------------[ThrowMissle]---------------------------------------

	StartIndex = 8;
	IndexCount = 5;
	InterTimer = 0.1f;
	Loop = false;

	Monster_Hidegons::AniParams[static_cast<int>(Hidegons_AniType::Right_ThrowMissle)] = FrameAnimationParameter
	{
		.AnimationName = "Right_ThrowMissle",
		.ImageName = Monster_Hidegons::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Hidegons::AniParams[static_cast<int>(Hidegons_AniType::Left_ThrowMissle)] = FrameAnimationParameter
	{
		.AnimationName = "Left_ThrowMissle",
		.ImageName = Monster_Hidegons::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Hidegons::AniParams[static_cast<int>(Hidegons_AniType::Right_ThrowMissle_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_ThrowMissle_Rage",
		.ImageName = Monster_Hidegons::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Hidegons::AniParams[static_cast<int>(Hidegons_AniType::Left_ThrowMissle_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_ThrowMissle_Rage",
		.ImageName = Monster_Hidegons::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};
}