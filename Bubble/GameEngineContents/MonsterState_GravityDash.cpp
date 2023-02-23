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
	//���� ��ü���� �������� �켱 ó�� ����
	StateChangeFuncPtr IsChangeState = GetStateChangeFunc();
	if (nullptr != IsChangeState)
	{
		if (true == (GetMonster()->*IsChangeState)(_DeltaTime))
			return;
	}

	AccTime += _DeltaTime;

	//���� �ð��� �帣�� FSM ��ȯ
	if (DashDuration < AccTime)
	{
		//���� ���߿� �־ Falling�� �˾Ƽ� falling���� �ٲ��ٰ���
		GetFSM()->ChangeState(MonsterStateType::Move);
		return;
	}

	//���߿� �ִٸ� �Ʒ��� �̵�
	if (false == GetMonster()->IsGround(MonsterBase::CollisionScale))
	{
		//�Ʒ��� �̵�
		GetMonster()->SetMove(float4::Down * DashGravity * _DeltaTime);

		//ĳ���Ͱ� ȭ�� �Ʒ��� �������ٸ� ���� �ø���
		float4 ScreenSize = GameEngineWindow::GetScreenSize();
		float4 NowPos = GetMonster()->GetPos();
		if (ScreenSize.y + ScreenOutOffsetY < NowPos.y)
		{
			//y�� 0���� �����
			GetMonster()->SetPos({ NowPos.x, 10.f });

			//Stage������ ������ ���װ� ����� Falling���·� �ٲ������
			//�ƴϸ� �Ʒ��� RaiseOnGround���� ȭ�� ���� �ö����� �Ʒ��� ������ �ڵ带 ����
			GetFSM()->ChangeState(MonsterStateType::Falling);
		}
	}

	//�׷��� �ʴٸ� �������� �̵�
	else
	{
		GetMonster()->RaiseOnGround(MonsterBase::CollisionScale);

		//�����̰� ���� �����ٸ� false�� return
		if (false == GetMonster()->MoveHorizon(DashSpeed.x, MonsterBase::CollisionScale, _DeltaTime))
		{
			//������ �ݴ�� ��ȯ
			GetMonster()->SetReverseDir();
		}
	}

	//�÷��̾�� �浹������
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
