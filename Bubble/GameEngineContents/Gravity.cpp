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
	//MovableActor�� �����ϴ� ������ RoundLevel �� ����
	GameEngineLevel* Level = GetOwner()->GetLevel();
	RoundLevel = dynamic_cast<RoundLevelBase*>(Level);
	if (nullptr == RoundLevel)
	{
		MsgAssert("���� ������ RoundLevelBase�� ��ӹ��� �ʾҽ��ϴ�");
	}

	//MovableActor�� ����
	MovableOwner = dynamic_cast<MovableActor*>(GetOwner());
	if (nullptr == MovableOwner)
	{
		MsgAssert("�� ������Ʈ�� ������ �ִ� ��ü�� MovableActor�� ��ӹ��� �ʾҽ��ϴ�");
	}
}

void Gravity::Update(float _DeltaTime)
{
	//���� ���ӵ� �� �޾ƿ���
	float NowGravityAcc = MovableOwner->GetGravityAcc();

	//������ġ
	float4 NowPos = GetOwner()->GetPos();
	//�ٷ� �Ʒ� ��ġ
	float4 DownPos = NowPos + float4::Down;

	//�Ʒ��� �������� ���(���ӵ� ���� ���)
	if (0.f <= NowGravityAcc)
	{
		//�� �ٷ� ���� �ٴ��϶���
		if (true == RoundLevel->IsBlockPos(DownPos))
		{
			//���ӵ� 0
			MovableOwner->SetGravityAcc(0.f);

			//���ӵ��� �ʹ� ���� �÷��̾ ���� �Ĺ������� ���� ������ �۾�
			while (RoundLevel->IsBlockPos(NowPos))
			{
				//���� �ƴҶ� ���� ���� �ø���
				NowPos += float4::Up;
			}

			GetOwner()->SetPos(NowPos);
			return;
		}
	}

	//���� �ö󰡴� ���, �����ϴ� ���(���ӵ� ���� ����)
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
