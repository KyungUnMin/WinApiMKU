#include "Monster_PuruPuru.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "MonsterFSM.h"
#include "MonsterState_PuruFly.h"
#include "MonsterState_Lock.h"
#include "MonsterState_Dead.h"
#include "MonsterState_Falling.h"

const std::string_view		Monster_PuruPuru::ImagePath			= "PuruPuru_Fly.bmp";
const std::string_view		Monster_PuruPuru::LockImagePath	= "PuruPuru_Lock.bmp";
const std::string_view		Monster_PuruPuru::DeadImagePath = "PuruPuru_Dead.bmp";

Monster_PuruPuru::Monster_PuruPuru()
{

}

Monster_PuruPuru::~Monster_PuruPuru()
{

}

void Monster_PuruPuru::Start()
{
	MonsterBase::Start();
	ResourceLoad();
	GetRender()->SetPosition(float4::Zero);
	GetCollision()->SetPosition(float4::Zero);

	MonsterState_Falling* FallingState = GetFSM()->CreateState<MonsterState_Falling>(MonsterStateType::Falling);
	FallingState->SetStateChangeFunc((StateChangeFuncPtr)&Monster_PuruPuru::FallingToFly);

	MonsterState_PuruFly* FlyState = GetFSM()->CreateState<MonsterState_PuruFly>(MonsterStateType::PuruFly);
	MonsterState_Lock* LockState = GetFSM()->CreateState<MonsterState_Lock>(MonsterStateType::Lock);
	MonsterState_Dead* DeadState = GetFSM()->CreateState<MonsterState_Dead>(MonsterStateType::Dead);

	for (size_t i = 0; i < AniParams.size(); ++i)
	{
		GetRender()->CreateAnimation(AniParams[i]);
	}

	Start_FSM(MonsterStateType::PuruFly);
}

void Monster_PuruPuru::ResourceLoad()
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
	Dir.Move("PuruPuru");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(ImagePath))->Cut(4, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LockImagePath))->Cut(3, 2);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(DeadImagePath))->Cut(4, 1);
	IsLoad = true;
}

bool Monster_PuruPuru::FallingToFly(float _DeltaTime)
{
	if (false == IsAlreadyFall)
	{
		GetFSM()->ChangeState(MonsterStateType::PuruFly);
		IsAlreadyFall = true;
	}
	else
	{
		GetFSM()->ChangeState(MonsterStateType::Dead);
	}
	
	return true;
}
