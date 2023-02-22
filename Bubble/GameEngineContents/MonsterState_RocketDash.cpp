#include "MonsterState_RocketDash.h"
#include "MonsterFSM.h"
#include "PlayerBase.h"


MonsterState_RocketDash::MonsterState_RocketDash()
{

}

MonsterState_RocketDash::~MonsterState_RocketDash()
{

}

void MonsterState_RocketDash::Start()
{
	MonsterStateBase::Start();
	SetNowAniName("RocketDash");
}

void MonsterState_RocketDash::Update(float _DeltaTime)
{
	//���� ��ü���� �������� �켱 ó�� ����
	StateChangeFuncPtr IsChangeState = GetStateChangeFunc();
	if (nullptr != IsChangeState)
	{
		if (true == (GetMonster()->*IsChangeState)(_DeltaTime))
			return;
	}

	//�������� ó���ϰ� ���� �����ٸ�
	if (false == GetMonster()->MoveHorizon(DashSpeed.x, MonsterBase::CollisionScale, _DeltaTime))
	{
		//���� ���߿� �־ Falling�� �� ��
		GetFSM()->ChangeState(MonsterStateType::Move);
		return;
	}

	//�÷��̾�� �浹������
	if (true == PlayerCollisionCheck())
	{
		PlayerBase::MainPlayer->AttackPlayer();
		return;
	}
}
