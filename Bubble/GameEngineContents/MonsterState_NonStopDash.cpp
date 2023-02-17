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
		//���� ���� �ӹ����־ Falling�� �˾Ƽ� move�� �ٲ��ٰ���
		GetFSM()->ChangeState(MonsterStateType::Falling);
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
			GetMonster()->SetPos(NowPos * float4::Right);
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

