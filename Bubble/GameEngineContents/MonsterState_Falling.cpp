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
	//State�� ����Ǿ����� return
	if (true == CheckStateChange(_DeltaTime))
		return;

	Move(_DeltaTime);

	//�÷��̾�� �浹������
	if (true == PlayerCollisionCheck())
	{
		PlayerBase::MainPlayer->AttackPlayer();
		return;
	}
}

void MonsterState_Falling::EnterState()
{
	MonsterStateBase::EnterState();

	//Falling���� ��ȯ������ �� ���ο� �����ߴ��� üũ
	IsBlocked = GetMonster()->IsGround(MonsterBase::CollisionScale);
}


bool MonsterState_Falling::CheckStateChange(float _DeltaTime)
{
	//���� ��ü���� �������� �켱 ó�� ����
	StateChangeFuncPtr IsChangeState = GetStateChangeFunc();
	if (nullptr != IsChangeState)
	{
		if (true == (GetMonster()->*IsChangeState)())
			return true;
	}

	//Falling���°� �Ǿ����� �� �ȿ� �־���, ���� �� ���� �������Դٸ�
	if ((true == IsBlocked) && false == GetMonster()->IsGround(MonsterBase::CollisionScale))
	{
		//�������� ���� ������� Idle���·� ��ȯ����
		IsBlocked = false;
	}

	//���� ��Ҵٸ� Idle���·� ��ȯ
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
	//�Ʒ��� �̵�
	GetMonster()->SetMove(float4::Down * GravitySpeed * _DeltaTime);

	//ĳ���Ͱ� ȭ�� �Ʒ��� �������ٸ� ���� �ø���
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	float4 NowPos = GetMonster()->GetPos();
	if (ScreenSize.y + ScreenOutOffsetY < NowPos.y)
	{
		//y�� 0���� �����
		GetMonster()->SetPos(NowPos * float4::Right);
	}
}

