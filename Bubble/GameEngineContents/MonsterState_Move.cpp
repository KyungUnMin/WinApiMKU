#include "MonsterState_Move.h"
#include <GameEngineCore/GameEngineRender.h>
#include "MonsterFSM.h"

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
		if (true == (GetMonster()->*IsChangeState)())
			return;
	}

	//임시 테스트 코드 (허공에 떠있는 경우)
	//실제로는 플레이어 위치에 따라서 점프할 지 내려갈지 결정되는듯 하다
	if (false == GetMonster()->IsGround(MonsterBase::CollisionScale))
	{
		GetFSM()->ChangeState(MonsterStateType::Falling);
		return;
	}

	//몬스터 이동
	if (false == GetMonster()->MoveHorizon(MoveSpeed.x, MonsterBase::CollisionScale, _DeltaTime))
	{
		//길이 막혔다면 반대 방향으로 이동
		GetMonster()->SetReverseDir();
		GameEngineRender* RenderPtr = GetMonster()->GetRender();

		std::string NextAniName = GetMonster()->GetDirStr() + GetNowAniName();
		RenderPtr->ChangeAnimation(NextAniName, true);
	}
}
