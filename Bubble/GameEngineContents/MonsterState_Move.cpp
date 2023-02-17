#include "MonsterState_Move.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "MonsterFSM.h"
#include "ContentsEnum.h"
#include "PlayerBase.h"

MonsterState_Move::MonsterState_Move()
{

}

MonsterState_Move::~MonsterState_Move()
{

}

void MonsterState_Move::Start()
{
	SetNowAniName("Move");
}

void MonsterState_Move::Update(float _DeltaTime)
{
	//몬스터 객체에서 지정해준 우선 처리 사항
	StateChangeFuncPtr IsChangeState = GetStateChangeFunc();
	if (nullptr != IsChangeState)
	{
		if (true == (GetMonster()->*IsChangeState)(_DeltaTime))
			return;
	}

	//플레이어와 몬스터의 거리가 PlayerFindRange 이내이고, 플레이어가 위에 있다면 점프
	if (HorizonSizeWithPlayer()  < PlayerFindRange && true == IsPlayerPosOver())
	{
		//50%의 확률로만 점프
		if (0 == rand() % CaseDoJump)
		{
			GetMonster()->SetReverseDir();
			GetFSM()->ChangeState(MonsterStateType::Jump);
			return;
		}
	}

	//땅 끝에 도달한 경우
	if (false == GetMonster()->IsGround(MonsterBase::CollisionScale))
	{
		//플레이어가 자신보다 위에 있으면 점프
		if (true == IsPlayerPosOver())
		{
			GetMonster()->SetDir(GetHorizonDirToPlayer());
			GetFSM()->ChangeState(MonsterStateType::Jump);
		}

		//아래에 있는 경우엔 떨어지기
		else
		{
			GetFSM()->ChangeState(MonsterStateType::Falling);
		}

		return;
	}

	//몬스터 이동
	if (false == GetMonster()->MoveHorizon(MoveSpeed.x, MonsterBase::CollisionScale, _DeltaTime))
	{
		//막혔을때 플레이어가 위에 있다면 점프
		if (true == IsPlayerPosOver())
		{
			GetMonster()->SetReverseDir();
			GetFSM()->ChangeState(MonsterStateType::Jump);
			return;
		}
		else
		{
			//플레이어 위치와 동일하거나 플레이어 위에 있다면 방향 전환
			GetMonster()->SetReverseDir();
			GameEngineRender* RenderPtr = GetMonster()->GetRender();

			std::string NextAniName = GetMonster()->GetDirStr() + GetNowAniName();
			RenderPtr->ChangeAnimation(NextAniName, true);
		}
		
	}

	//플레이어와 충돌했을때
	if (true == PlayerCollisionCheck())
	{
		PlayerBase::MainPlayer->AttackPlayer();
		return;
	}
}

bool MonsterState_Move::IsPlayerPosOver()
{
	//플레이어가 죽은 경우엔 항상 false
	if (nullptr == PlayerBase::MainPlayer)
		return false;
	
	float4 PlayerPos = PlayerBase::MainPlayer->GetPos();
	float4 MonsterPos = GetMonster()->GetPos();

	//내 위치가 플레이어보다 아래에 있다면 true 리턴(윈도우 좌표계)
	return (PlayerPos.y < MonsterPos.y);
}

float MonsterState_Move::HorizonSizeWithPlayer()
{
	if (nullptr == PlayerBase::MainPlayer)
	{
		return FLT_MAX;
	}

	float4 PlayerPos = PlayerBase::MainPlayer->GetPos();
	float4 MonsterPos = GetMonster()->GetPos();

	return abs(PlayerPos.x - MonsterPos.x);
}