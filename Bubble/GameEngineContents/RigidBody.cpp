#include "RigidBody.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineActor.h>

RigidBody::RigidBody()
{

}

RigidBody::~RigidBody()
{

}

void RigidBody::Update(float _DeltaTime)
{
	if (nullptr == Owner)
	{
		MsgAssert("RigidBody Ŭ������ Owner�� ���������� �ʾҽ��ϴ�");
		return;
	}


	//���� ���ӵ��� ����
	CalcForce();

	//�߰� ���ӵ�
	Acceleration += AccelAlpha;

	//(���ӵ� * �ð� = �ӷ�), ���ӵ���ŭ �ӷ� ���ϱ�
	Velocity += Acceleration * _DeltaTime;

	//�������� �ӵ��� ����
	CalcFric(_DeltaTime);

	//�ִ� �ӵ� ����
	LimitSpeed();

	//�ӵ��� ���� �̵�ó��
	Move(_DeltaTime);

	//�� ���ӵ��� �ʱ�ȭ��Ű��?
	ForceVec = float4::Zero;
	Acceleration = float4::Zero;
	AccelAlpha = float4::Zero;
}

void RigidBody::CalcForce()
{
	//���� �����Ҷ���
	if (true == ForceVec.IsZero())
		return;

	//���� ũ��
	float Force = ForceVec.Size();

	//�� ���� ����ȭ
	ForceVec.Normalize();

	//(F = ma) -> (a = F / m)
	//���ӵ� ũ��
	float Acc = Force / Mass;

	//���ӵ�
	Acceleration = ForceVec * Acc;
}

void RigidBody::CalcFric(float _DeltaTime)
{
	//�ӵ��� 0�� �ƴҶ���
	if (true == Velocity.IsZero())
		return;

	//���� ����(��������)
	float4 FricDir = -Velocity;
	FricDir.Normalize();

	//������ = �������� * ������� * �ð�
	float4 Friction = FricDir * FricCoef * _DeltaTime;

	//���� �ӵ��� �����º��� ������ 0, ū ��쿣 ����ӵ� - ������
	if (Velocity.Size() <= Friction.Size())
		Velocity = float4::Zero;
	else
		Velocity += Friction;
}

void RigidBody::LimitSpeed()
{
	//X�� �ִ�ӵ� ����
	float NowSpeedX = abs(Velocity.x);
	float MaxSpeedX = abs(MaxVelocity.x);
	if (MaxSpeedX < NowSpeedX)
	{
		//������ �״��, �ӵ��� MaxSpeed��
		Velocity.x = (Velocity.x / NowSpeedX) * MaxSpeedX;
	}

	//Y�� �ִ�ӵ� ����
	float NowSpeedY = abs(Velocity.y);
	float MaxSpeedY = abs(MaxVelocity.y);
	if (MaxSpeedY < NowSpeedY)
	{
		//������ �״��, �ӵ��� MaxSpeed��
		Velocity.y = (Velocity.y / NowSpeedY) * MaxSpeedY;
	}
}

void RigidBody::Move(float _DeltaTime)
{
	if (true == Velocity.IsZero())
		return;

	float4 Dir = Velocity;
	Dir.Normalize();
	float Speed = Velocity.Size();
	if (0.f == Speed)
		return;

	float4 Pos = Owner->GetPos();
	Pos += Velocity * _DeltaTime;
	Owner->SetPos(Pos);
}
