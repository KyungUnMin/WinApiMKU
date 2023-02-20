#include "MonsterState_ReflectionFly.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "RoundLevelBase.h"
#include "PlayerBase.h"

MonsterState_ReflectionFly::MonsterState_ReflectionFly()
{

}

MonsterState_ReflectionFly::~MonsterState_ReflectionFly()
{

}




void MonsterState_ReflectionFly::Start()
{
	SetNowAniName("ReflectionFly");
	RoundLevel = dynamic_cast<RoundLevelBase*>(GetMonster()->GetLevel());
	if (nullptr == RoundLevel)
	{
		MsgAssert("몬스터가 RoundLevel이 아닌 곳에서 생성되었습니다");
		return;
	}

	MoveDir.Normalize();
}

void MonsterState_ReflectionFly::EnterState()
{
	if (0.f <= MoveDir.x)
	{
		GetMonster()->SetDir(float4::Right);
	}
	else
	{
		GetMonster()->SetDir(float4::Left);
	}

	MonsterStateBase::EnterState();
}


void MonsterState_ReflectionFly::Update(float _DeltaTime)
{
	//몬스터 객체에서 지정해준 우선 처리 사항
	StateChangeFuncPtr IsChangeState = GetStateChangeFunc();
	if (nullptr != IsChangeState)
	{
		if (true == (GetMonster()->*IsChangeState)(_DeltaTime))
			return;
	}

	Move(_DeltaTime);

	if (true == PlayerCollisionCheck())
	{
		PlayerBase::MainPlayer->AttackPlayer();
		return;
	}
}



void MonsterState_ReflectionFly::Move(float _DeltaTime)
{
	MonsterBase* Monster = GetMonster();

	//현재위치
	float4 NowPos = Monster->GetPos();

	//다음 위치
	float4 NextPos = NowPos + MoveDir * MoveSpeed * _DeltaTime;
	float4 CheckPos = NextPos + MoveDir * RotateRange;

	if (false == RoundLevel->IsBlockPos(CheckPos) && false == IsScreenOut(CheckPos))
	{
		Monster->SetPos(NextPos);
		return;
	}

	//회전하기 전 방향 저장
	float PrevDirX = MoveDir.x;

	//벡터 회전
	float Radian = Angle * GameEngineMath::DegToRad;
	float4 NextDir = float4::Zero;
	NextDir.x = MoveDir.x* cosf(Radian) - MoveDir.y * sinf(Radian);
	NextDir.y = MoveDir.x* sinf(Radian) + MoveDir.y * cosf(Radian);
	MoveDir = NextDir;

	//X축 방향이 바뀌였을때만
	if (0.f <= (PrevDirX * MoveDir.x))
		return;

	//x축 방향 뒤집기
	Monster->SetReverseDir();

	//애니메이션 교체
	ChangeAniDir();
}

bool MonsterState_ReflectionFly::IsScreenOut(const float4& _CheckPos)
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	if (_CheckPos.y < 0.f)
		return true;

	if (_CheckPos.x < 0.f)
		return true;

	if (ScreenSize.y < _CheckPos.y)
		return true;

	if (ScreenSize.x < _CheckPos.x)
		return true;

	return false;
}
