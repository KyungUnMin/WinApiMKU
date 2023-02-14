#include "Monster_ZenChan.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "MonsterFSM.h"


#include "MonsterState_Falling.h"
#include "MonsterState_Move.h"
#include "MonsterState_Jump.h"
#include "MonsterState_Lock.h"


const std::string_view		Monster_ZenChan::RightImagePath			= "Right_ZenChan.bmp";
const std::string_view		Monster_ZenChan::LeftImagePath			= "Left_ZenChan.bmp";
const std::string_view		Monster_ZenChan::RightRageImagePath	= "Right_ZenChan_Rage.bmp";
const std::string_view		Monster_ZenChan::LeftRageImagePath	= "Left_ZenChan_Rage.bmp";
const std::string_view		Monster_ZenChan::LockImagePath			= "ZenChan_Lock.bmp";
const std::string_view		Monster_ZenChan::DeadImagePath			= "ZenChan_Dead.bmp";


Monster_ZenChan::Monster_ZenChan()
{

}

Monster_ZenChan::~Monster_ZenChan()
{

}

void Monster_ZenChan::Start()
{
	MonsterBase::Start();
	ResourceLoad();

	MonsterState_Falling* FallingState = GetFSM()->CreateState<MonsterState_Falling>(MonsterStateType::Falling);
	MonsterState_Move* MoveState = GetFSM()->CreateState<MonsterState_Move>(MonsterStateType::Move);
	MoveState->SetStateChangeFunc((StateChangeFuncPtr)&Monster_ZenChan::Test);

	MonsterState_Jump* JumpState = GetFSM()->CreateState<MonsterState_Jump>(MonsterStateType::Jump);
	MonsterState_Lock* LockState = GetFSM()->CreateState<MonsterState_Lock>(MonsterStateType::Lock);


	for (size_t i = 0; i < AniParams.size(); ++i)
	{
		GetRender()->CreateAnimation(AniParams[i]);
	}

	Start_FSM(MonsterStateType::Falling);
}



void Monster_ZenChan::ResourceLoad()
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
	Dir.Move("ZenChan");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightImagePath))->Cut(4, 3);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftImagePath))->Cut(4, 3);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightRageImagePath))->Cut(4, 3);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftRageImagePath))->Cut(4, 3);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LockImagePath))->Cut(3, 2);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(DeadImagePath))->Cut(4, 1);
	IsLoad = true;
}