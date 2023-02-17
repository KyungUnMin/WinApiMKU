#include "MonsterState_Jump.h"
#include "MonsterFSM.h"
#include "PlayerBase.h"

MonsterState_Jump::MonsterState_Jump()
{

}

MonsterState_Jump::~MonsterState_Jump()
{

}

void MonsterState_Jump::Start()
{
	SetNowAniName("Jump");
}


void MonsterState_Jump::EnterState()
{
	MonsterStateBase::EnterState();
	AccTime = 0.0f;
}

void MonsterState_Jump::Update(float _DeltaTime)
{
	AccTime += _DeltaTime;

	if (true == CheckStateChange(_DeltaTime))
		return;

	//플레이어와 충돌했을때
	if (true == PlayerCollisionCheck())
	{
		PlayerBase::MainPlayer->AttackPlayer();
		return;
	}
}


bool MonsterState_Jump::CheckStateChange(float _DeltaTime)
{
	//몬스터 객체에서 지정해준 우선 처리 사항
	StateChangeFuncPtr IsChangeState = GetStateChangeFunc();
	if (nullptr != IsChangeState)
	{
		if (true == (GetMonster()->*IsChangeState)(_DeltaTime))
			return true;
	}

	//점프 유지 시간이 전부 지났을때
	if (FallingChangeTime < AccTime)
	{
		GetFSM()->ChangeState(MonsterStateType::Falling);
		return true;
	}

	//움직이다가 점프를 못하는 상황일때
	if (false == Movement(_DeltaTime))
	{
		GetFSM()->ChangeState(MonsterStateType::Falling);
		return true;
	}

	return false;
}

bool MonsterState_Jump::Movement(float _DeltaTime)
{
	float Ratio = AccTime / FallingChangeTime;
	float4 NowJumpSpeed = float4::LerpClamp(JumpSpeed, float4::Zero, Ratio);

	float4 NowPos = GetMonster()->GetPos();
	float4 NowDir = GetMonster()->GetDirVec();
	float4 NextPos = NowPos + (float4{ NowDir.x, -1.f } *NowJumpSpeed * _DeltaTime);
	float4 CollisionScale = MonsterBase::CollisionScale;
	float PlayerHeight = CollisionScale.Size();

	//다음에 이동할 위치가 스크린을 넘어간다면
	if (NextPos.y - PlayerHeight < ScreenTopOffset)
		return false;

	GetMonster()->SetPos(NextPos);

	return true;
}
