#include "Gravity.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineActor.h>
#include "RoundLevelBase.h"
#include "MovableActor.h"

Gravity::Gravity()
{

}

Gravity::~Gravity()
{

}


void Gravity::Start()
{
	GameEngineLevel* Level = GetOwner()->GetLevel();
	RoundLevel = dynamic_cast<RoundLevelBase*>(Level);
	if (nullptr == RoundLevel)
	{
		MsgAssert("RoundLevel�� ���� ������ ����Ǿ� ���� �ʽ��ϴ�");
	}

	MovableOwner = dynamic_cast<MovableActor*>(GetOwner());
	if (nullptr == MovableOwner)
	{
		MsgAssert("�� ������Ʈ�� ������ �ִ� ��ü�� MovableActor�� ��ӹ��� �ʾҽ��ϴ�");
	}
}

void Gravity::Update(float _DeltaTime)
{
	float4 NowPos = GetOwner()->GetPos();
	float4 NextPos = NowPos + float4::Down;
	if (true == RoundLevel->IsBlockPos(NextPos))
	{
		MovableOwner->SetGravityAcc(0.f);
		return;
	}

	MovableOwner->SetMoveGravityAcc(GravityCoef * _DeltaTime);
	GetOwner()->SetMove(float4::Down * MovableOwner->GetGravityAcc() * _DeltaTime);
}

//������ ���� ������ �ȵ�
//���� PlayerState���� ����� �ٰ�

//void Gravity::Jump(float _JumpAcc)
//{
//	float4 BelowPos = GetOwner()->GetPos() + float4::Down;
//
//	//���߿� �ִ� ���
//	if (false == RoundLevel->IsBlockPos(BelowPos))
//		return;
//
//	MovableOwner->SetGravityAcc(_JumpAcc);
//}