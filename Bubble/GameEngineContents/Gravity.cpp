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
	float NowGravityAcc = MovableOwner->GetGravityAcc();

	float4 NowPos = GetOwner()->GetPos();
	float4 DownPos = NowPos + float4::Down;

	//�Ʒ��� �������� ���(���)
	if (0.f <= NowGravityAcc)
	{
		//�� �ٷ� ���� �ٴ��̶��
		if (true == RoundLevel->IsBlockPos(DownPos))
		{
			//���ӵ� 0
			MovableOwner->SetGravityAcc(0.f);
			return;
		}
	}

	//���� �ö󰡴� ���(����)
	else
	{
		//�� �ٷ� ���� �ٴ��̰� �� ��ġ�� �ٴ��� �ƴҶ���
		if (true == RoundLevel->IsBlockPos(DownPos) && false == RoundLevel->IsBlockPos(NowPos))
		{
			//���ӵ� 0
			MovableOwner->SetGravityAcc(0.f);
			return;
		}
	}

	//�߷� ���ӵ� ���ϱ�
	MovableOwner->SetMoveGravityAcc(GravityCoef * _DeltaTime);

	//�߷°��ӵ��� ���� ����ŭ �̵�(float4::Down�� Up���� �ٲٸ� ����� �� ������ �� ����)
	GetOwner()->SetMove(float4::Down * NowGravityAcc * _DeltaTime);

	//���⼭ ���� �Ĺ��� ��� ����ó�� �ؾ� �� �� �� ����
}
