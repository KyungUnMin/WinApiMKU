#include "Monster_HeitaKun.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>

#include "MonsterFSM.h"
#include "MonsterState_Falling.h"
#include "MonsterState_Move.h"
#include "MonsterState_Jump.h"
#include "MonsterState_Lock.h"
#include "MonsterState_Dead.h"

const std::string_view		Monster_HeitaKun::RightImagePath				= "Right_HeitaKun.bmp";
const std::string_view		Monster_HeitaKun::LeftImagePath				= "Left_HeitaKun.bmp";
const std::string_view		Monster_HeitaKun::RightRageImagePath		= "Right_HeitaKun_Rage.bmp";
const std::string_view		Monster_HeitaKun::LeftRageImagePath		= "Left_HeitaKun_Rage.bmp";
const std::string_view		Monster_HeitaKun::LockImagePath				= "HeitaKun_Lock.bmp";
const std::string_view		Monster_HeitaKun::DeadImagePath				= "HeitaKun_Dead.bmp";

Monster_HeitaKun::Monster_HeitaKun()
{

}

Monster_HeitaKun::~Monster_HeitaKun()
{

}


void Monster_HeitaKun::Start()
{
	MonsterBase::Start();
	ResourceLoad();

	MonsterState_Falling* FallingState = GetFSM()->CreateState<MonsterState_Falling>(MonsterStateType::Falling);
	MonsterState_Move* MoveState = GetFSM()->CreateState<MonsterState_Move>(MonsterStateType::Move);
	MonsterState_Jump* JumpState = GetFSM()->CreateState<MonsterState_Jump>(MonsterStateType::Jump);
	JumpState->SetJumpSpeed({ 0.f, 700.f });

	MonsterState_Lock* LockState = GetFSM()->CreateState<MonsterState_Lock>(MonsterStateType::Lock);
	MonsterState_Dead* DeadState = GetFSM()->CreateState<MonsterState_Dead>(MonsterStateType::Dead);


	for (size_t i = 0; i < AniParams.size(); ++i)
	{
		GetRender()->CreateAnimation(AniParams[i]);
	}

	Start_FSM(MonsterStateType::Falling);
}

void Monster_HeitaKun::ResourceLoad()
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
	Dir.Move("HeitaKun");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightImagePath))->Cut(4, 2);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftImagePath))->Cut(4, 2);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightRageImagePath))->Cut(4, 2);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftRageImagePath))->Cut(4, 2);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LockImagePath))->Cut(3, 2);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(DeadImagePath))->Cut(4, 1);
	IsLoad = true;
}
