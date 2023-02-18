#include "Monster_Magician.h"
#include <GameEngineCore/GameEngineRender.h>
#include "MonsterFSM.h"

std::vector<FrameAnimationParameter> Monster_Magician::AniParams;

class Magician_AniParamInit
{
public:
	Magician_AniParamInit();
	~Magician_AniParamInit(){}
};

Magician_AniParamInit Init_Magician = Magician_AniParamInit();

Magician_AniParamInit::Magician_AniParamInit()
{
	Monster_Magician::AniParams.resize(static_cast<int>(Magician_AniType::Count));

	//-------------------------------------------------------[Move]----------------------------------------------

	int StartIndex = 0;
	int IndexCount = 6;
	float InterTimer = 0.1f;
	bool Loop = true;

	Monster_Magician::AniParams[static_cast<int>(Magician_AniType::Right_Move)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Move",
		.ImageName = Monster_Magician::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Magician::AniParams[static_cast<int>(Magician_AniType::Left_Move)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Move",
		.ImageName = Monster_Magician::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Magician::AniParams[static_cast<int>(Magician_AniType::Right_Move_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Move_Rage",
		.ImageName = Monster_Magician::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Magician::AniParams[static_cast<int>(Magician_AniType::Left_Move_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Move_Rage",
		.ImageName = Monster_Magician::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//-----------------------------------------------------------[Falling]-----------------------------------------

	StartIndex = 8;
	IndexCount = 2;
	InterTimer = 0.1f;

	Monster_Magician::AniParams[static_cast<int>(Magician_AniType::Right_Falling)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Falling",
		.ImageName = Monster_Magician::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Magician::AniParams[static_cast<int>(Magician_AniType::Left_Falling)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Falling",
		.ImageName = Monster_Magician::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Magician::AniParams[static_cast<int>(Magician_AniType::Right_Falling_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Falling_Rage",
		.ImageName = Monster_Magician::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Magician::AniParams[static_cast<int>(Magician_AniType::Left_Falling_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Falling_Rage",
		.ImageName = Monster_Magician::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//------------------------------------------------------------[Jump]-----------------------------------------

	StartIndex = 6;
	IndexCount = 2;
	InterTimer = 0.1f;

	Monster_Magician::AniParams[static_cast<int>(Magician_AniType::Right_Jump)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Jump",
		.ImageName = Monster_Magician::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Magician::AniParams[static_cast<int>(Magician_AniType::Left_Jump)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Jump",
		.ImageName = Monster_Magician::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};


	Monster_Magician::AniParams[static_cast<int>(Magician_AniType::Right_Jump_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Jump_Rage",
		.ImageName = Monster_Magician::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Magician::AniParams[static_cast<int>(Magician_AniType::Left_Jump_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Jump_Rage",
		.ImageName = Monster_Magician::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//---------------------------------------------------------------------[Lock]---------------------------------------

	StartIndex = 0;
	IndexCount = 3;
	InterTimer = 0.25f;

	Monster_Magician::AniParams[static_cast<int>(Magician_AniType::Lock)] = FrameAnimationParameter
	{
		.AnimationName = "Lock",
		.ImageName = Monster_Magician::LockImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	StartIndex = 3;
	IndexCount = 3;

	Monster_Magician::AniParams[static_cast<int>(Magician_AniType::Lock_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Lock_Rage",
		.ImageName = Monster_Magician::LockImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//---------------------------------------------------------------------[Dead]---------------------------------------

	StartIndex = 0;
	IndexCount = 4;
	InterTimer = 0.1f;

	Monster_Magician::AniParams[static_cast<int>(Magician_AniType::Dead)] = FrameAnimationParameter
	{
		.AnimationName = "Dead",
		.ImageName = Monster_Magician::DeadImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

}
