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


void Gravity::Start(GameEngineActor* _Owner)
{
	Owner = _Owner;

	GameEngineLevel* Level = Owner->GetLevel();
	RoundLevel = dynamic_cast<RoundLevelBase*>(Level);
	if (nullptr == RoundLevel)
	{
		MsgAssert("���� ������ RoundLevelBase�� ��ӹ��� �ʾҽ��ϴ�");
	}
}

void Gravity::Update(float _DeltaTime)
{
	if (false == GlobalGravityUse)
		return;

	//������ġ
	float4 NowPos = Owner->GetPos();
	
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
			NowGravityAcc = 0.f;

			//���ӵ��� �ʹ� ���� �÷��̾ ���� �Ĺ������� ���� ������ �۾�
			while (RoundLevel->IsBlockPos(NowPos))
			{
				//���� �ƴҶ� ���� ���� �ø���
				NowPos += float4::Up;
			}

			Owner->SetPos(NowPos);
			return;
		}
	}

	
	PrevGravityAcc = NowGravityAcc;

	//�߷� ���ӵ� ���ϱ�
	NowGravityAcc += GravityCoef * _DeltaTime;

	//�߷°��ӵ��� ���� ����ŭ �̵�(float4::Down�� Up���� �ٲٸ� ����� �� ������ �� ����)
	Owner->SetMove(float4::Down * NowGravityAcc * _DeltaTime);
}
