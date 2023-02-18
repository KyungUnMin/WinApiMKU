#include "Monster_Warurin.h"
#include <GameEngineCore/GameEngineRender.h>
#include "MonsterFSM.h"

std::vector<FrameAnimationParameter> Monster_Warurin::AniParams;

class Warurin_AniParamInit
{
public:
	Warurin_AniParamInit();
	~Warurin_AniParamInit()
	{

	}
};

Warurin_AniParamInit Init_MightA = Warurin_AniParamInit();

Warurin_AniParamInit::Warurin_AniParamInit()
{
	Monster_Warurin::AniParams.resize(static_cast<int>(Warurin_AniType::Count));

	//-------------------------------------------------------[Move]----------------------------------------------

	int StartIndex = 0;
	int IndexCount = 6;
	float InterTimer = 0.1f;
	bool Loop = true;

	Monster_Warurin::AniParams[static_cast<int>(Warurin_AniType::Right_Move)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Move",
		.ImageName = Monster_Warurin::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Warurin::AniParams[static_cast<int>(Warurin_AniType::Left_Move)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Move",
		.ImageName = Monster_Warurin::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Warurin::AniParams[static_cast<int>(Warurin_AniType::Right_Move_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Move_Rage",
		.ImageName = Monster_Warurin::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Warurin::AniParams[static_cast<int>(Warurin_AniType::Left_Move_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Move_Rage",
		.ImageName = Monster_Warurin::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//-----------------------------------------------------------[Falling]-----------------------------------------

	StartIndex = 8;
	IndexCount = 2;
	InterTimer = 0.1f;
	Loop = true;

	Monster_Warurin::AniParams[static_cast<int>(Warurin_AniType::Right_Falling)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Falling",
		.ImageName = Monster_Warurin::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Warurin::AniParams[static_cast<int>(Warurin_AniType::Left_Falling)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Falling",
		.ImageName = Monster_Warurin::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Warurin::AniParams[static_cast<int>(Warurin_AniType::Right_Falling_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Falling_Rage",
		.ImageName = Monster_Warurin::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Warurin::AniParams[static_cast<int>(Warurin_AniType::Left_Falling_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Falling_Rage",
		.ImageName = Monster_Warurin::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//------------------------------------------------------------[Jump]-----------------------------------------

	StartIndex = 6;
	IndexCount = 2;
	InterTimer = 0.1f;
	Loop = true;

	Monster_Warurin::AniParams[static_cast<int>(Warurin_AniType::Right_Jump)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Jump",
		.ImageName = Monster_Warurin::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Warurin::AniParams[static_cast<int>(Warurin_AniType::Left_Jump)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Jump",
		.ImageName = Monster_Warurin::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};


	Monster_Warurin::AniParams[static_cast<int>(Warurin_AniType::Right_Jump_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_Jump_Rage",
		.ImageName = Monster_Warurin::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Warurin::AniParams[static_cast<int>(Warurin_AniType::Left_Jump_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_Jump_Rage",
		.ImageName = Monster_Warurin::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//---------------------------------------------------------------------[Lock]---------------------------------------

	StartIndex = 0;
	IndexCount = 3;
	InterTimer = 0.25f;

	Monster_Warurin::AniParams[static_cast<int>(Warurin_AniType::Lock)] = FrameAnimationParameter
	{
		.AnimationName = "Lock",
		.ImageName = Monster_Warurin::LockImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	StartIndex = 3;
	IndexCount = 3;

	Monster_Warurin::AniParams[static_cast<int>(Warurin_AniType::Lock_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Lock_Rage",
		.ImageName = Monster_Warurin::LockImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//---------------------------------------------------------------------[Dead]---------------------------------------

	StartIndex = 0;
	IndexCount = 4;
	InterTimer = 0.1f;

	Monster_Warurin::AniParams[static_cast<int>(Warurin_AniType::Dead)] = FrameAnimationParameter
	{
		.AnimationName = "Dead",
		.ImageName = Monster_Warurin::DeadImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	//---------------------------------------------------------------------[ThrowMissle]---------------------------------------

	StartIndex = 10;
	IndexCount = 4;
	InterTimer = 0.1f;
	Loop = false;

	Monster_Warurin::AniParams[static_cast<int>(Warurin_AniType::Right_ThrowMissle)] = FrameAnimationParameter
	{
		.AnimationName = "Right_ThrowMissle",
		.ImageName = Monster_Warurin::RightImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Warurin::AniParams[static_cast<int>(Warurin_AniType::Left_ThrowMissle)] = FrameAnimationParameter
	{
		.AnimationName = "Left_ThrowMissle",
		.ImageName = Monster_Warurin::LeftImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Warurin::AniParams[static_cast<int>(Warurin_AniType::Right_ThrowMissle_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Right_ThrowMissle_Rage",
		.ImageName = Monster_Warurin::RightRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};

	Monster_Warurin::AniParams[static_cast<int>(Warurin_AniType::Left_ThrowMissle_Rage)] = FrameAnimationParameter
	{
		.AnimationName = "Left_ThrowMissle_Rage",
		.ImageName = Monster_Warurin::LeftRageImagePath,
		.Start = StartIndex,
		.End = StartIndex + IndexCount - 1,
		.InterTimer = InterTimer,
		.Loop = Loop
	};
}