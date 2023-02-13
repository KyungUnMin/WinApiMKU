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
	//���� ��ü���� �������� �켱 ó�� ����
	StateChangeFuncPtr IsChangeState = GetStateChangeFunc();
	if (nullptr != IsChangeState)
	{
		if (true == (GetMonster()->*IsChangeState)())
			return;
	}

	//�ӽ� �׽�Ʈ �ڵ� (����� ���ִ� ���)
	//�����δ� �÷��̾� ��ġ�� ���� ������ �� �������� �����Ǵµ� �ϴ�
	if (false == GetMonster()->IsGround(MonsterBase::CollisionScale))
	{
		GetFSM()->ChangeState(MonsterStateType::Falling);
		return;
	}

	//���� �̵�
	if (false == GetMonster()->MoveHorizon(MoveSpeed.x, MonsterBase::CollisionScale, _DeltaTime))
	{
		//���� �����ٸ� �ݴ� �������� �̵�
		GetMonster()->SetReverseDir();
		GameEngineRender* RenderPtr = GetMonster()->GetRender();

		std::string NextAniName = GetMonster()->GetDirStr() + GetNowAniName();
		RenderPtr->ChangeAnimation(NextAniName, true);
	}
}
