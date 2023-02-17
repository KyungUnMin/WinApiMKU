#include "MonsterState_Move.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "MonsterFSM.h"
#include "ContentsEnum.h"
#include "PlayerBase.h"

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
		if (true == (GetMonster()->*IsChangeState)(_DeltaTime))
			return;
	}

	//�÷��̾�� ������ �Ÿ��� PlayerFindRange �̳��̰�, �÷��̾ ���� �ִٸ� ����
	if (HorizonSizeWithPlayer()  < PlayerFindRange && true == IsPlayerPosOver())
	{
		//50%�� Ȯ���θ� ����
		if (0 == rand() % CaseDoJump)
		{
			GetMonster()->SetReverseDir();
			GetFSM()->ChangeState(MonsterStateType::Jump);
			return;
		}
	}

	//�� ���� ������ ���
	if (false == GetMonster()->IsGround(MonsterBase::CollisionScale))
	{
		//�÷��̾ �ڽź��� ���� ������ ����
		if (true == IsPlayerPosOver())
		{
			GetMonster()->SetDir(GetHorizonDirToPlayer());
			GetFSM()->ChangeState(MonsterStateType::Jump);
		}

		//�Ʒ��� �ִ� ��쿣 ��������
		else
		{
			GetFSM()->ChangeState(MonsterStateType::Falling);
		}

		return;
	}

	//���� �̵�
	if (false == GetMonster()->MoveHorizon(MoveSpeed.x, MonsterBase::CollisionScale, _DeltaTime))
	{
		//�������� �÷��̾ ���� �ִٸ� ����
		if (true == IsPlayerPosOver())
		{
			GetMonster()->SetReverseDir();
			GetFSM()->ChangeState(MonsterStateType::Jump);
			return;
		}
		else
		{
			//�÷��̾� ��ġ�� �����ϰų� �÷��̾� ���� �ִٸ� ���� ��ȯ
			GetMonster()->SetReverseDir();
			GameEngineRender* RenderPtr = GetMonster()->GetRender();

			std::string NextAniName = GetMonster()->GetDirStr() + GetNowAniName();
			RenderPtr->ChangeAnimation(NextAniName, true);
		}
		
	}

	//�÷��̾�� �浹������
	if (true == PlayerCollisionCheck())
	{
		PlayerBase::MainPlayer->AttackPlayer();
		return;
	}
}

bool MonsterState_Move::IsPlayerPosOver()
{
	//�÷��̾ ���� ��쿣 �׻� false
	if (nullptr == PlayerBase::MainPlayer)
		return false;
	
	float4 PlayerPos = PlayerBase::MainPlayer->GetPos();
	float4 MonsterPos = GetMonster()->GetPos();

	//�� ��ġ�� �÷��̾�� �Ʒ��� �ִٸ� true ����(������ ��ǥ��)
	return (PlayerPos.y < MonsterPos.y);
}

float MonsterState_Move::HorizonSizeWithPlayer()
{
	if (nullptr == PlayerBase::MainPlayer)
	{
		return FLT_MAX;
	}

	float4 PlayerPos = PlayerBase::MainPlayer->GetPos();
	float4 MonsterPos = GetMonster()->GetPos();

	return abs(PlayerPos.x - MonsterPos.x);
}