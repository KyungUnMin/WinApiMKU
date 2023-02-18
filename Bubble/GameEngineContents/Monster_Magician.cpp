#include "Monster_Magician.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>

#include "MonsterFSM.h"
#include "MonsterState_Falling.h"
#include "MonsterState_Move.h"
#include "MonsterState_Jump.h"
#include "MonsterState_Lock.h"
#include "MonsterState_Dead.h"

const std::string_view		Monster_Magician::RightImagePath			= "Right_Magician.bmp";
const std::string_view		Monster_Magician::LeftImagePath			= "Left_Magician.bmp";
const std::string_view		Monster_Magician::RightRageImagePath	= "Right_Magician_Rage.bmp";
const std::string_view		Monster_Magician::LeftRageImagePath	= "Left_Magician_Rage.bmp";
const std::string_view		Monster_Magician::LockImagePath			= "Magician_Lock.bmp";
const std::string_view		Monster_Magician::DeadImagePath			= "Magician_Dead.bmp";


Monster_Magician::Monster_Magician()
{

}

Monster_Magician::~Monster_Magician()
{

}

void Monster_Magician::Start()
{
	MonsterBase::Start();
	ResourceLoad();

	MonsterState_Falling* FallingState = GetFSM()->CreateState<MonsterState_Falling>(MonsterStateType::Falling);
	MonsterState_Move* MoveState = GetFSM()->CreateState<MonsterState_Move>(MonsterStateType::Move);
	MonsterState_Jump* JumpState = GetFSM()->CreateState<MonsterState_Jump>(MonsterStateType::Jump);
	MonsterState_Lock* LockState = GetFSM()->CreateState<MonsterState_Lock>(MonsterStateType::Lock);
	MonsterState_Dead* DeadState = GetFSM()->CreateState<MonsterState_Dead>(MonsterStateType::Dead);

	for (size_t i = 0; i < AniParams.size(); ++i)
	{
		GetRender()->CreateAnimation(AniParams[i]);
	}

	Start_FSM(MonsterStateType::Falling);
}

void Monster_Magician::ResourceLoad()
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
	Dir.Move("Magician");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightImagePath))->Cut(6, 3);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftImagePath))->Cut(6, 3);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightRageImagePath))->Cut(6, 3);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftRageImagePath))->Cut(6, 3);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LockImagePath))->Cut(3, 2);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(DeadImagePath))->Cut(4, 1);
	IsLoad = true;
}
