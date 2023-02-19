#include "Monster_Myata.h"
#include <GameEngineCore/GameEngineRender.h>
#include "MonsterFSM.h"

std::vector<FrameAnimationParameter> Monster_Myata::AniParams;

class Myata_AniParamInit
{
public:
	Myata_AniParamInit();
	~Myata_AniParamInit() {}
};

Myata_AniParamInit Init_Myata = Myata_AniParamInit();

Myata_AniParamInit::Myata_AniParamInit()
{
	Monster_Myata::AniParams.resize(static_cast<int>(Myata_AniType::Count));

	//-------------------------------------------------------[Move]----------------------------------------------

	int StartIndex = 0;
	int IndexCount = 4;
	float InterTimer = 0.25f;
	bool Loop = true;

	Monster_Myata::AniParams[static_cast<int>(Myata_AniType::Right_Move)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Move",
		.ImageName = Monster_Myata::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Myata::AniParams[static_cast<int>(Myata_AniType::Left_Move)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Move",
		.ImageName = Monster_Myata::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Myata::AniParams[static_cast<int>(Myata_AniType::Right_Move_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Move_Rage",
		.ImageName = Monster_Myata::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Myata::AniParams[static_cast<int>(Myata_AniType::Left_Move_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Move_Rage",
		.ImageName = Monster_Myata::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//-----------------------------------------------------------[Falling]-----------------------------------------

	StartIndex = 6;
	IndexCount = 2;
	InterTimer = 0.1f;

	Monster_Myata::AniParams[static_cast<int>(Myata_AniType::Right_Falling)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Falling",
		.ImageName = Monster_Myata::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Myata::AniParams[static_cast<int>(Myata_AniType::Left_Falling)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Falling",
		.ImageName = Monster_Myata::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Myata::AniParams[static_cast<int>(Myata_AniType::Right_Falling_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Falling_Rage",
		.ImageName = Monster_Myata::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Myata::AniParams[static_cast<int>(Myata_AniType::Left_Falling_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Falling_Rage",
		.ImageName = Monster_Myata::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//------------------------------------------------------------[Jump]-----------------------------------------

	StartIndex = 4;
	IndexCount = 2;

	Monster_Myata::AniParams[static_cast<int>(Myata_AniType::Right_Jump)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Jump",
		.ImageName = Monster_Myata::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Myata::AniParams[static_cast<int>(Myata_AniType::Left_Jump)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Jump",
		.ImageName = Monster_Myata::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};


	Monster_Myata::AniParams[static_cast<int>(Myata_AniType::Right_Jump_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Jump_Rage",
		.ImageName = Monster_Myata::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Myata::AniParams[static_cast<int>(Myata_AniType::Left_Jump_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Jump_Rage",
		.ImageName = Monster_Myata::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//---------------------------------------------------------------------[Lock]---------------------------------------

	StartIndex = 0;
	IndexCount = 3;
	InterTimer = 0.25f;

	Monster_Myata::AniParams[static_cast<int>(Myata_AniType::Lock)] = FrameAnimationParameter
	{
		.AnimationName = "Lock",
		.ImageName = Monster_Myata::LockImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	StartIndex = 3;
	IndexCount = 3;

	Monster_Myata::AniParams[static_cast<int>(Myata_AniType::Lock_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Lock_Rage",
		.ImageName = Monster_Myata::LockImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//---------------------------------------------------------------------[Dead]---------------------------------------

	StartIndex = 0;
	IndexCount = 4;
	InterTimer = 0.1f;

	Monster_Myata::AniParams[static_cast<int>(Myata_AniType::Dead)] = FrameAnimationParameter
	{
		.AnimationName = "Dead",
		.ImageName = Monster_Myata::DeadImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//---------------------------------------------------------------[RigidDash]---------------------------------------

	StartIndex = 9;
	IndexCount = 2;
	InterTimer = 0.1f;
	Loop = true;

	Monster_Myata::AniParams[static_cast<int>(Myata_AniType::Right_Dash)] = FrameAnimationParameter
	{
		.AnimationName = "Right_RigidDash",
		.ImageName = Monster_Myata::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Myata::AniParams[static_cast<int>(Myata_AniType::Left_Dash)] = FrameAnimationParameter
	{
		.AnimationName = "Left_RigidDash",
		.ImageName = Monster_Myata::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Myata::AniParams[static_cast<int>(Myata_AniType::Right_Dash_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_RigidDash_Rage",
		.ImageName = Monster_Myata::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Myata::AniParams[static_cast<int>(Myata_AniType::Left_Dash_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_RigidDash_Rage",
		.ImageName = Monster_Myata::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//---------------------------------------------------------------[RigidDashReady]---------------------------------------

	StartIndex = 8;
	IndexCount = 2;
	InterTimer = 0.5f;
	Loop = false;

	Monster_Myata::AniParams[static_cast<int>(Myata_AniType::Right_DashReady)] = FrameAnimationParameter
	{
		.AnimationName = "Right_RigidReady",
		.ImageName = Monster_Myata::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Myata::AniParams[static_cast<int>(Myata_AniType::Left_DashReady)] = FrameAnimationParameter
	{
		.AnimationName = "Left_RigidReady",
		.ImageName = Monster_Myata::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Myata::AniParams[static_cast<int>(Myata_AniType::Right_DashReady_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_RigidReady_Rage",
		.ImageName = Monster_Myata::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Myata::AniParams[static_cast<int>(Myata_AniType::Left_DashReady_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_RigidReady_Rage",
		.ImageName = Monster_Myata::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};
}
