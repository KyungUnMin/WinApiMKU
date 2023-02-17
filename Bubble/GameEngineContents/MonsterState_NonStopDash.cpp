#include "MonsterState_NonStopDash.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include "MonsterFSM.h"
#include "PlayerBase.h"

MonsterState_NonStopDash::MonsterState_NonStopDash()
{

}

MonsterState_NonStopDash::~MonsterState_NonStopDash()
{

}

void MonsterState_NonStopDash::Start()
{
	SetNowAniName("NonStopDash");
}



void MonsterState_NonStopDash::EnterState()
{
	MonsterStateBase::EnterState();
	AccTime = 0.f;
}



void MonsterState_NonStopDash::Update(float _DeltaTime)
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
		//만약 땅에 머물러있어도 Falling이 알아서 move로 바꿔줄것임
		GetFSM()->ChangeState(MonsterStateType::Falling);
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
			GetMonster()->SetPos(NowPos * float4::Right);
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

