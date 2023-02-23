#include "MonsterState_GravityDash.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include "MonsterFSM.h"
#include "PlayerBase.h"

MonsterState_GravityDash::MonsterState_GravityDash()
{

}

MonsterState_GravityDash::~MonsterState_GravityDash()
{

}

void MonsterState_GravityDash::Start()
{
	SetNowAniName("GravityDash");
}



void MonsterState_GravityDash::EnterState()
{
	MonsterStateBase::EnterState();
	AccTime = 0.f;
}




void MonsterState_GravityDash::Update(float _DeltaTime)
{
	//몬스터 객체에서 지정해준 우선 처리 사항
	StateChangeFuncPtr IsChangeState = GetStateChangeFunc();
	if (nullptr != IsChangeState)
	{
		if (true == (GetMonster()->*IsChangeState)(_DeltaTime))
			return;
	}

	AccTime += _DeltaTime;

	//일정 시간이 흐르면 FSM 전환
	if (DashDuration < AccTime)
	{
		//만약 공중에 있어도 Falling이 알아서 falling으로 바꿔줄것임
		GetFSM()->ChangeState(MonsterStateType::Move);
		return;
	}

	//공중에 있다면 아래로 이동
	if (false == GetMonster()->IsGround(MonsterBase::CollisionScale))
	{
		//아래로 이동
		GetMonster()->SetMove(float4::Down * DashGravity * _DeltaTime);

		//캐릭터가 화면 아래로 내려갔다면 위로 올리기
		float4 ScreenSize = GameEngineWindow::GetScreenSize();
		float4 NowPos = GetMonster()->GetPos();
		if (ScreenSize.y + ScreenOutOffsetY < NowPos.y)
		{
			//y를 0으로 만들기
			GetMonster()->SetPos({ NowPos.x, 10.f });

			//Stage밖으로 나가는 버그가 생기면 Falling상태로 바꿔버리자
			//아니면 아래의 RaiseOnGround에서 화면 위로 올라갔을때 아래로 내리는 코드를 넣자
			GetFSM()->ChangeState(MonsterStateType::Falling);
		}
	}

	//그렇지 않다면 수평으로 이동
	else
	{
		GetMonster()->RaiseOnGround(MonsterBase::CollisionScale);

		//움직이고 벽에 막혔다면 false를 return
		if (false == GetMonster()->MoveHorizon(DashSpeed.x, MonsterBase::CollisionScale, _DeltaTime))
		{
			//방향을 반대로 전환
			GetMonster()->SetReverseDir();
		}
	}

	//플레이어와 충돌했을때
	if (true == PlayerCollisionCheck())
	{
		PlayerBase::MainPlayer->AttackPlayer();
		return;
	}
}


void MonsterState_GravityDash::ExitState()
{
	GetMonster()->RaiseOnGround(MonsterBase::CollisionScale);
}
