#include "Monster_Warurin.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>

#include "MonsterFSM.h"
#include "MonsterState_Falling.h"
#include "MonsterState_Move.h"
#include "MonsterState_Jump.h"
#include "MonsterState_Lock.h"
#include "MonsterState_Dead.h"
#include "MonsterState_ThrowMissle.h"

#include "PlayerBase.h"


const std::string_view		Monster_Warurin::RightImagePath			= "Right_Warurin.bmp";
const std::string_view		Monster_Warurin::LeftImagePath				= "Left_Warurin.bmp";
const std::string_view		Monster_Warurin::RightRageImagePath	= "Right_Warurin_Rage.bmp";
const std::string_view		Monster_Warurin::LeftRageImagePath		= "Left_Warurin_Rage.bmp";
const std::string_view		Monster_Warurin::LockImagePath			= "Warurin_Lock.bmp";
const std::string_view		Monster_Warurin::DeadImagePath			= "Warurin_Dead.bmp";

Monster_Warurin::Monster_Warurin()
{
	
}

Monster_Warurin::~Monster_Warurin()
{

}

void Monster_Warurin::Start()
{
	MonsterBase::Start();
	ResourceLoad();

	MonsterState_Falling* FallingState = GetFSM()->CreateState<MonsterState_Falling>(MonsterStateType::Falling);
	MonsterState_Move* MoveState = GetFSM()->CreateState<MonsterState_Move>(MonsterStateType::Move);
	MoveState->SetStateChangeFunc((StateChangeFuncPtr)&Monster_Warurin::MoveToThrow);
	MoveState->SetSpeed({ 100.f, 0.f });

	MonsterState_Jump* JumpState = GetFSM()->CreateState<MonsterState_Jump>(MonsterStateType::Jump);
	MonsterState_Lock* LockState = GetFSM()->CreateState<MonsterState_Lock>(MonsterStateType::Lock);
	MonsterState_Dead* DeadState = GetFSM()->CreateState<MonsterState_Dead>(MonsterStateType::Dead);
	MonsterState_ThrowMissle* ThrowMissleState = GetFSM()->CreateState<MonsterState_ThrowMissle>(MonsterStateType::ThrowMissle);
	ThrowMissleState->SetMissleType(MonMissleType::WarurinBress);

	for (size_t i = 0; i < AniParams.size(); ++i)
	{
		GetRender()->CreateAnimation(AniParams[i]);
	}

	Start_FSM(MonsterStateType::Falling);
}

void Monster_Warurin::ResourceLoad()
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
	Dir.Move("Warurin");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightImagePath))->Cut(6, 3);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftImagePath))->Cut(6, 3);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightRageImagePath))->Cut(6, 3);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftRageImagePath))->Cut(6, 3);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LockImagePath))->Cut(3, 2);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(DeadImagePath))->Cut(4, 1);
	IsLoad = true;
}

bool Monster_Warurin::MoveToThrow(float _DeltaTime)
{
	static const float FindHeightRange = 100.f;
	static float Timer = 0.0f;
	static const float ThrowTime = 3.f;

	float4 PlayerPos = PlayerBase::MainPlayer->GetPos();
	float4 ThisPos = GetPos();

	//플레이어와의 높이차이가 FindHeightRange 미만일때만
	if (FindHeightRange < abs(PlayerPos.y - ThisPos.y))
		return false;

	Timer += _DeltaTime;
	if (Timer < ThrowTime)
		return false;

	//플레이어 바라보기
	float4 Dir = (PlayerPos.x < ThisPos.x) ? float4::Left : float4::Right;
	SetDir(Dir);
	Timer -= ThrowTime;

	GetFSM()->ChangeState(MonsterStateType::ThrowMissle);
	return true;
}
