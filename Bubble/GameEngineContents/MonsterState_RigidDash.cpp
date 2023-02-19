#include "MonsterState_RigidDash.h"
#include <GameEngineCore/GameEngineRender.h>
#include "MonsterFSM.h"
#include "PlayerBase.h"

const std::string_view MonsterState_RigidDash::ReadyAniName		= "RigidReady";
const std::string_view MonsterState_RigidDash::DashAniName			= "RigidDash";

MonsterState_RigidDash::MonsterState_RigidDash()
{

}

MonsterState_RigidDash::~MonsterState_RigidDash()
{

}

void MonsterState_RigidDash::EnterState()
{
	SetNowAniName(ReadyAniName);
	MonsterStateBase::EnterState();
	NowState = State::Ready;
	MoveAccTime = 0.f;
}



void MonsterState_RigidDash::Update(float _DeltaTime)
{
	//몬스터 객체에서 지정해준 우선 처리 사항
	StateChangeFuncPtr IsChangeState = GetStateChangeFunc();
	if (nullptr != IsChangeState)
	{
		if (true == (GetMonster()->*IsChangeState)(_DeltaTime))
			return;
	}

	Movement(_DeltaTime);
	
	//플레이어와 충돌했을때
	if (true == PlayerCollisionCheck())
	{
		PlayerBase::MainPlayer->AttackPlayer();
		return;
	}
}




void MonsterState_RigidDash::Movement(float _DeltaTime)
{
	if (State::Ready == NowState)
	{
		if (false == GetMonster()->GetRender()->IsAnimationEnd())
			return;

		size_t Index = GetMonster()->GetRender()->GetFrame();

		NowState = State::Dash;
		SetNowAniName(DashAniName);
		ChangeAniDir();
		return;
	}

	MoveAccTime += _DeltaTime;
	if (MoveDuration < MoveAccTime)
	{
		GetFSM()->ChangeState(MonsterStateType::Move);
		return;
	}

	if (false == GetMonster()->IsGround(MonsterBase::CollisionScale))
		return;

	float Ratio = MoveAccTime / MoveDuration;
	float4 NowSpeed = float4::LerpClamp(StartSpeed, float4::Zero, Ratio);
	GetMonster()->MoveHorizon(NowSpeed.x, MonsterBase::CollisionScale, _DeltaTime);
}