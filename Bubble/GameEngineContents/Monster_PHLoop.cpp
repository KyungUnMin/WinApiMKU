#include "Monster_PHLoop.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>

#include "MonsterFSM.h"
#include "MonsterState_Falling.h"
#include "MonsterState_Move.h"
#include "MonsterState_Jump.h"
#include "MonsterState_Lock.h"
#include "MonsterState_Dead.h"
#include "MonsterState_GravityDash.h"

const std::string_view		Monster_PHLoop::RightImagePath			= "Right_PLHoop.bmp";
const std::string_view		Monster_PHLoop::LeftImagePath				= "Left_PLHoop.bmp";
const std::string_view		Monster_PHLoop::RightRageImagePath	= "Right_PHLoop_Rage.bmp";
const std::string_view		Monster_PHLoop::LeftRageImagePath		= "Left_PHLoop_Rage.bmp";
const std::string_view		Monster_PHLoop::LockImagePath				= "PHLoop_Lock.bmp";
const std::string_view		Monster_PHLoop::DeadImagePath			= "PHLoop_Dead.bmp";

Monster_PHLoop::Monster_PHLoop()
{

}

Monster_PHLoop::~Monster_PHLoop()
{

}

void Monster_PHLoop::Start()
{
	MonsterBase::Start();
	ResourceLoad();

	MonsterState_Falling* FallingState = GetFSM()->CreateState<MonsterState_Falling>(MonsterStateType::Falling);
	MonsterState_Move* MoveState = GetFSM()->CreateState<MonsterState_Move>(MonsterStateType::Move);
	MoveState->SetStateChangeFunc((StateChangeFuncPtr)&Monster_PHLoop::MoveToDash);

	MonsterState_Jump* JumpState = GetFSM()->CreateState<MonsterState_Jump>(MonsterStateType::Jump);
	MonsterState_Lock* LockState = GetFSM()->CreateState<MonsterState_Lock>(MonsterStateType::Lock);
	MonsterState_Dead* DeadState = GetFSM()->CreateState<MonsterState_Dead>(MonsterStateType::Dead);

	MonsterState_GravityDash* DashState = GetFSM()->CreateState<MonsterState_GravityDash>(MonsterStateType::GravityDash);

	for (size_t i = 0; i < AniParams.size(); ++i)
	{
		GetRender()->CreateAnimation(AniParams[i]);
	}

	Start_FSM(MonsterStateType::Falling);
}

void Monster_PHLoop::ResourceLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Monster");
	Dir.Move("PHLoop");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightImagePath))->Cut(4, 5);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftImagePath))->Cut(4, 5);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightRageImagePath))->Cut(4, 5);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftRageImagePath))->Cut(4, 5);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LockImagePath))->Cut(3, 2);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(DeadImagePath))->Cut(4, 1);
	IsLoad = true;
}

bool Monster_PHLoop::MoveToDash(float _DeltaTime)
{
	static float Timer = 0.0f;
	static const float DashTime = 3.f;
	Timer += _DeltaTime;

	if (DashTime < Timer)
	{
		Timer -= DashTime;
		GetFSM()->ChangeState(MonsterStateType::GravityDash);
		return true;
	}

	return false;
}
