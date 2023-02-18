#include "Monster_MightA.h"
#include <GameEngineCore/GameEngineRender.h>
#include "MonsterFSM.h"

std::vector<FrameAnimationParameter> Monster_MightA::AniParams;

class MightA_AniParamInit
{
public:
	MightA_AniParamInit();
	~MightA_AniParamInit()
	{

	}
};

MightA_AniParamInit Init_ZenChan = MightA_AniParamInit();

MightA_AniParamInit::MightA_AniParamInit()
{
	Monster_MightA::AniParams.resize(static_cast<int>(MightA_AniType::Count));

	//-------------------------------------------------------[Move]----------------------------------------------

	int StartIndex = 0;
	int IndexCount = 4;
	float InterTimer = 0.1f;
	bool Loop = true;

	Monster_MightA::AniParams[static_cast<int>(MightA_AniType::Right_Move)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Move",
		.ImageName = Monster_MightA::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_MightA::AniParams[static_cast<int>(MightA_AniType::Left_Move)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Move",
		.ImageName = Monster_MightA::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_MightA::AniParams[static_cast<int>(MightA_AniType::Right_Move_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Move_Rage",
		.ImageName = Monster_MightA::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_MightA::AniParams[static_cast<int>(MightA_AniType::Left_Move_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Move_Rage",
		.ImageName = Monster_MightA::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//-----------------------------------------------------------[Falling]-----------------------------------------

	StartIndex = 6;
	IndexCount = 2;
	InterTimer = 0.1f;
	Loop = true;

	Monster_MightA::AniParams[static_cast<int>(MightA_AniType::Right_Falling)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Falling",
		.ImageName = Monster_MightA::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_MightA::AniParams[static_cast<int>(MightA_AniType::Left_Falling)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Falling",
		.ImageName = Monster_MightA::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_MightA::AniParams[static_cast<int>(MightA_AniType::Right_Falling_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Falling_Rage",
		.ImageName = Monster_MightA::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_MightA::AniParams[static_cast<int>(MightA_AniType::Left_Falling_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Falling_Rage",
		.ImageName = Monster_MightA::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//------------------------------------------------------------[Jump]-----------------------------------------

	StartIndex = 4;
	IndexCount = 2;
	InterTimer = 0.1f;
	Loop = true;

	Monster_MightA::AniParams[static_cast<int>(MightA_AniType::Right_Jump)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Jump",
		.ImageName = Monster_MightA::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_MightA::AniParams[static_cast<int>(MightA_AniType::Left_Jump)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Jump",
		.ImageName = Monster_MightA::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};


	Monster_MightA::AniParams[static_cast<int>(MightA_AniType::Right_Jump_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Jump_Rage",
		.ImageName = Monster_MightA::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_MightA::AniParams[static_cast<int>(MightA_AniType::Left_Jump_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Jump_Rage",
		.ImageName = Monster_MightA::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//---------------------------------------------------------------------[Lock]---------------------------------------

	StartIndex = 0;
	IndexCount = 3;
	InterTimer = 0.25f;

	Monster_MightA::AniParams[static_cast<int>(MightA_AniType::Lock)] = FrameAnimationParameter
	{
		.AnimationName = "Lock",
		.ImageName = Monster_MightA::LockImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	StartIndex = 3;
	IndexCount = 3;

	Monster_MightA::AniParams[static_cast<int>(MightA_AniType::Lock_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Lock_Rage",
		.ImageName = Monster_MightA::LockImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//---------------------------------------------------------------------[Dead]---------------------------------------

	StartIndex = 0;
	IndexCount = 4;
	InterTimer = 0.1f;

	Monster_MightA::AniParams[static_cast<int>(MightA_AniType::Dead)] = FrameAnimationParameter
	{
		.AnimationName = "Dead",
		.ImageName = Monster_MightA::DeadImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

}