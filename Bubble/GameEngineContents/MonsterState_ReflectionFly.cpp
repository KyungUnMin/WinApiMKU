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
		MsgAssert("���Ͱ� RoundLevel�� �ƴ� ������ �����Ǿ����ϴ�");
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
	//���� ��ü���� �������� �켱 ó�� ����
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

	//������ġ
	float4 NowPos = Monster->GetPos();

	//���� ��ġ
	float4 NextPos = NowPos + MoveDir * MoveSpeed * _DeltaTime;
	float4 CheckPos = NextPos + MoveDir * RotateRange;

	if (false == RoundLevel->IsBlockPos(CheckPos) && false == IsScreenOut(CheckPos))
	{
		Monster->SetPos(NextPos);
		return;
	}

	//ȸ���ϱ� �� ���� ����
	float PrevDirX = MoveDir.x;

	//���� ȸ��
	float Radian = Angle * GameEngineMath::DegToRad;
	float4 NextDir = float4::Zero;
	NextDir.x = MoveDir.x* cosf(Radian) - MoveDir.y * sinf(Radian);
	NextDir.y = MoveDir.x* sinf(Radian) + MoveDir.y * cosf(Radian);
	MoveDir = NextDir;

	//X�� ������ �ٲ������
	if (0.f <= (PrevDirX * MoveDir.x))
		return;

	//x�� ���� ������
	Monster->SetReverseDir();

	//�ִϸ��̼� ��ü
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
