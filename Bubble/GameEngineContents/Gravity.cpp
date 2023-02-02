#include "Gravity.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineActor.h>
#include "RoundLevelBase.h"
#include "MovableActor.h"

bool Gravity::GlobalGravityUse = true;

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
	if (false == GlobalGravityUse)
		return;

	//������ġ
	float4 NowPos = GetOwner()->GetPos();
	
	//���� ���ӵ� �� �޾ƿ���
	float NowGravityAcc = MovableOwner->GetGravityAcc();

	//�����ϴٰ� �Ʒ��� �������� ���
	if (0.f < NowGravityAcc && PrevGravityAcc < 0.f)
	{
		//���������� Stage�� ���� ���
		if (true == RoundLevel->IsBlockPos(NowPos))
		{
			IsTouchCollision = true;
		}
		else
		{
			IsTouchCollision = false;
		}
	}

	//�ݸ������� �������� ���
	if (true == IsTouchCollision && false == RoundLevel->IsBlockPos(NowPos))
	{
		IsTouchCollision = false;
	}

	if (false == IsTouchCollision)
	{
		//�ٷ� �Ʒ� ��ġ
		float4 DownPos = NowPos + float4::Down;

		//�Ʒ��� �������� ���(���ӵ� ���� ���)�鼭 �� �ٷ� ���� �ٴ��϶�
		if (0.f <= NowGravityAcc && RoundLevel->IsBlockPos(DownPos))
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

	//�߷� ���ӵ� ���ϱ�
	MovableOwner->SetMoveGravityAcc(GravityCoef * _DeltaTime);

	//�߷°��ӵ��� ���� ����ŭ �̵�(float4::Down�� Up���� �ٲٸ� ����� �� ������ �� ����)
	GetOwner()->SetMove(float4::Down * NowGravityAcc * _DeltaTime);

	
	PrevGravityAcc = NowGravityAcc;
}
