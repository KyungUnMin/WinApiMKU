#include "MonsterState_Falling.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include "MonsterBase.h"
#include "MonsterFSM.h"
#include "PlayerBase.h"

MonsterState_Falling::MonsterState_Falling()
{

}

MonsterState_Falling::~MonsterState_Falling()
{

}

void MonsterState_Falling::Start()
{
	SetNowAniName("Falling");
}

void MonsterState_Falling::Update(float _DeltaTime)
{
	//State가 변경되었으면 return
	if (true == CheckStateChange(_DeltaTime))
		return;

	Move(_DeltaTime);

	//플레이어와 충돌했을때
	if (true == PlayerCollisionCheck())
	{
		PlayerBase::MainPlayer->AttackPlayer();
		return;
	}
}

void MonsterState_Falling::EnterState()
{
	MonsterStateBase::EnterState();

	//Falling으로 전환됐을때 벽 내부에 존재했는지 체크
	IsBlocked = GetMonster()->IsGround(MonsterBase::CollisionScale);
}


bool MonsterState_Falling::CheckStateChange(float _DeltaTime)
{
	//몬스터 객체에서 지정해준 우선 처리 사항
	StateChangeFuncPtr IsChangeState = GetStateChangeFunc();
	if (nullptr != IsChangeState)
	{
		if (true == (GetMonster()->*IsChangeState)())
			return true;
	}

	//Falling상태가 되었을때 벽 안에 있었고, 이젠 그 벽을 빠져나왔다면
	if ((true == IsBlocked) && false == GetMonster()->IsGround(MonsterBase::CollisionScale))
	{
		//이제부터 땅에 닿았을때 Idle상태로 변환가능
		IsBlocked = false;
	}

	//땅에 닿았다면 Idle상태로 전환
	if (false == IsBlocked && true == GetMonster()->IsGround(MonsterBase::CollisionScale))
	{
		GetFSM()->ChangeState(MonsterStateType::Move);
		GetMonster()->RaiseOnGround(MonsterBase::CollisionScale);
		return true;
	}

	return false;
}

void MonsterState_Falling::Move(float _DeltaTime)
{
	//아래로 이동
	GetMonster()->SetMove(float4::Down * GravitySpeed * _DeltaTime);

	//캐릭터가 화면 아래로 내려갔다면 위로 올리기
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	float4 NowPos = GetMonster()->GetPos();
	if (ScreenSize.y + ScreenOutOffsetY < NowPos.y)
	{
		//y를 0으로 만들기
		GetMonster()->SetPos(NowPos * float4::Right);
	}
}

