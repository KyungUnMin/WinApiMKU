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
#include "MonsterState_RocketDash.h"

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
	MoveState->SetStateChangeFunc((StateChangeFuncPtr)&Monster_Magician::MagicianMoveStep);
	MoveState->SetSpeed(float4{ 250.f, 0.f });

	MonsterState_Jump* JumpState = GetFSM()->CreateState<MonsterState_Jump>(MonsterStateType::Jump);
	MonsterState_Lock* LockState = GetFSM()->CreateState<MonsterState_Lock>(MonsterStateType::Lock);
	MonsterState_Dead* DeadState = GetFSM()->CreateState<MonsterState_Dead>(MonsterStateType::Dead);

	MonsterState_RocketDash* RocketDash = GetFSM()->CreateState<MonsterState_RocketDash>(MonsterStateType::RocketDash);

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












bool Monster_Magician::MagicianMoveStep(float _DeltaTime)
{
	static const float ResumeTime = 0.5f;
	static float AniTime = 0.0f;
	static const int RocketDashProbability = 50;

	GameEngineRender* RenderPtr = GetRender();

	//애니메이션이 진행중이면 그대로 MoveState진행
	if (false == RenderPtr->IsAnimationEnd())
		return false;

	//일정 시간 동안은 움직이지 않는다
	AniTime += _DeltaTime;
	if (AniTime < ResumeTime)
		return true;

	//특정 확률로 로켓대쉬 발동
	if (0 == (rand() % RocketDashProbability))
	{
		GetFSM()->ChangeState(MonsterStateType::RocketDash);
		return true;
	}

	//정지 시간이 흐르고 나면 원래대로 이동 재개
	std::string NowAniName = GetDirStr() + "Move";
	RenderPtr->ChangeAnimation(NowAniName, true);
	AniTime -= ResumeTime;
	return false;
}
