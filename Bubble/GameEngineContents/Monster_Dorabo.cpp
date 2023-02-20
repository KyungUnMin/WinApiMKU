#include "Monster_Dorabo.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>

#include "MonsterFSM.h"
#include "MonsterState_HorizonFly.h"
#include "MonsterState_Tired.h"
#include "MonsterState_Falling.h"
#include "MonsterState_VerticalShake.h"
#include "MonsterState_Dizzy.h"
#include "MonsterState_RaiseFly.h"
#include "MonsterState_Lock.h"
#include "MonsterState_Dead.h"

const std::string_view		Monster_Dorabo::RightImagePath			= "Right_Dorabo.bmp";
const std::string_view		Monster_Dorabo::LeftImagePath				= "Left_Dorabo.bmp";
const std::string_view		Monster_Dorabo::RightRageImagePath	= "Right_Dorabo_Rage.bmp";
const std::string_view		Monster_Dorabo::LeftRageImagePath		= "Left_Dorabo_Rage.bmp";
const std::string_view		Monster_Dorabo::LockImagePath				= "Dorabo_Lock.bmp";
const std::string_view		Monster_Dorabo::DeadImagePath				= "Dorabo_Dead.bmp";

Monster_Dorabo::Monster_Dorabo()
{

}

Monster_Dorabo::~Monster_Dorabo()
{

}

void Monster_Dorabo::Start()
{
	MonsterBase::Start();
	ResourceLoad();

	MonsterState_HorizonFly* FlyState = GetFSM()->CreateState<MonsterState_HorizonFly>(MonsterStateType::HorizonFly);
	MonsterState_Tired* TiredState = GetFSM()->CreateState<MonsterState_Tired>(MonsterStateType::Tired);
	MonsterState_Falling* FallState = GetFSM()->CreateState<MonsterState_Falling>(MonsterStateType::Falling);
	FallState->SetStateChangeFunc((StateChangeFuncPtr)&Monster_Dorabo::FallToShake);
	FallState->SetGravitySpeed(FallSpeed);

	MonsterState_VerticalShake* ShakeState = GetFSM()->CreateState<MonsterState_VerticalShake>(MonsterStateType::VerticalShake);
	MonsterState_Dizzy* DizzyState = GetFSM()->CreateState<MonsterState_Dizzy>(MonsterStateType::Dizzy);
	MonsterState_RaiseFly* RaiseState = GetFSM()->CreateState<MonsterState_RaiseFly>(MonsterStateType::RaiseFly);

	MonsterState_Lock* LockState = GetFSM()->CreateState<MonsterState_Lock>(MonsterStateType::Lock);
	MonsterState_Dead* DeadState = GetFSM()->CreateState<MonsterState_Dead>(MonsterStateType::Dead);

	for (size_t i = 0; i < AniParams.size(); ++i)
	{
		GetRender()->CreateAnimation(AniParams[i]);
	}

	Start_FSM(MonsterStateType::Falling);
}

void Monster_Dorabo::ResourceLoad()
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
	Dir.Move("Dorabo");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightImagePath))->Cut(4, 3);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftImagePath))->Cut(4, 3);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightRageImagePath))->Cut(4, 3);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftRageImagePath))->Cut(4, 3);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LockImagePath))->Cut(3, 2);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(DeadImagePath))->Cut(4, 1);
	IsLoad = true;
}

bool Monster_Dorabo::FallToShake(float _DeltaTime)
{
	//¶¥¿¡ ¾È ´ê¾Ò´Ù¸é ±×´ë·Î ÁøÇà
	if (false == IsGround(MonsterBase::CollisionScale))
		return false;

	//¶¥¿¡ ´ê¾Ò´Ù¸é (¶¥¿¡ ¹ÚÇûÀ»¶§¸¦ ´ëºñÇØ) ¶¥ À§ ¿Ã¸®°í »óÅÂ º¯°æ
	RaiseOnGround(MonsterBase::CollisionScale);
	GetFSM()->ChangeState(MonsterStateType::VerticalShake);
	return true;
}


