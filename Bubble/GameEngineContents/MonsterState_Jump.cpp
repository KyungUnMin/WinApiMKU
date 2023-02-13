#include "MonsterState_Jump.h"
#include "MonsterFSM.h"

MonsterState_Jump::MonsterState_Jump()
{

}

MonsterState_Jump::~MonsterState_Jump()
{

}

void MonsterState_Jump::Start()
{
	SetNowAniName("Jump");
	AccTime = 0.0f;
}

void MonsterState_Jump::Update(float _DeltaTime)
{
	AccTime += _DeltaTime;

	if (true == CheckStateChange(_DeltaTime))
		return;

}

bool MonsterState_Jump::CheckStateChange(float _DeltaTime)
{
	//몬스터 객체에서 지정해준 우선 처리 사항
	StateChangeFuncPtr IsChangeState = GetStateChangeFunc();
	if (nullptr != IsChangeState)
	{
		if (true == (GetMonster()->*IsChangeState)())
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
	float4 NextPos = NowPos + (float4::Up * NowJumpSpeed * _DeltaTime);
	float4 CollisionScale = MonsterBase::CollisionScale;
	float PlayerHeight = CollisionScale.Size();

	//다음에 이동할 위치가 스크린을 넘어간다면
	if (NextPos.y - PlayerHeight < ScreenTopOffset)
		return false;

	GetMonster()->SetPos(NextPos);

	return true;
}
