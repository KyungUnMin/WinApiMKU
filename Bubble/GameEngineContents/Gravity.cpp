#include "Gravity.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineActor.h>
#include "RoundLevelBase.h"
#include "MovableActor.h"
#include "BubbleCore.h"

Gravity::Gravity()
{

}

Gravity::~Gravity()
{
	
}


void Gravity::Start(GameEngineActor* _Owner, const float4& _CollisionScale)
{
	Owner = _Owner;
	CollisionScale = _CollisionScale;

	GameEngineLevel* Level = Owner->GetLevel();
	RoundLevel = dynamic_cast<RoundLevelBase*>(Level);
	if (nullptr == RoundLevel)
	{
		MsgAssert("���� ������ RoundLevelBase�� ��ӹ��� �ʾҽ��ϴ�");
	}
}

void Gravity::Update(float _DeltaTime)
{
	if (false == UseGravity)
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
		//�浹ü���� ��¦ ���� ���� ����(�ٷ� �Ʒ�)
		float4 LeftCheckPos = (NowPos + float4::Left * CollisionScale.half()) + float4::Down + float4::Right;
		float4 RightCheckPos = (NowPos + float4::Right * CollisionScale.half()) + float4::Down + float4::Left;

		//�Ʒ��� �������� ���(���ӵ� ���� ���)�鼭 �� �ٷ� ���� �ٴ��϶�
		if (0.f <= NowGravityAcc && (RoundLevel->IsBlockPos(LeftCheckPos) || RoundLevel->IsBlockPos(RightCheckPos)))
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

void Gravity::DebugRender()
{
	if (false == BubbleCore::GetInst().IsDebug())
		return;

	GameEngineLevel::DebugTextPush(std::to_string(NowGravityAcc));
}

void Gravity::On()
{
	UseGravity = true;
}

void Gravity::Off()
{
	UseGravity = false;
	NowGravityAcc = 0.0f;
	PrevGravityAcc = 0.0f;
	IsTouchCollision = false;
}
