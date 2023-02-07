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
		MsgAssert("RigidBody 클래스의 Owner를 설정해주지 않았습니다");
		return;
	}


	//힘을 가속도로 연산
	CalcForce();

	//추가 가속도
	Acceleration += AccelAlpha;

	//(가속도 * 시간 = 속력), 가속도만큼 속력 더하기
	Velocity += Acceleration * _DeltaTime;

	//마찰력을 속도로 연산
	CalcFric(_DeltaTime);

	//최대 속도 제한
	LimitSpeed();

	//속도에 따른 이동처리
	Move(_DeltaTime);

	//왜 가속도도 초기화시키지?
	ForceVec = float4::Zero;
	Acceleration = float4::Zero;
	AccelAlpha = float4::Zero;
}

void RigidBody::CalcForce()
{
	//힘이 존재할때만
	if (true == ForceVec.IsZero())
		return;

	//힘의 크기
	float Force = ForceVec.Size();

	//힘 벡터 정규화
	ForceVec.Normalize();

	//(F = ma) -> (a = F / m)
	//가속도 크기
	float Acc = Force / Mass;

	//가속도
	Acceleration = ForceVec * Acc;
}

void RigidBody::CalcFric(float _DeltaTime)
{
	//속도가 0이 아닐때만
	if (true == Velocity.IsZero())
		return;

	//저항 방향(마찰방향)
	float4 FricDir = -Velocity;
	FricDir.Normalize();

	//마찰력 = 마찰방향 * 마찰계수 * 시간
	float4 Friction = FricDir * FricCoef * _DeltaTime;

	//현재 속도가 마찰력보다 작으면 0, 큰 경우엔 현재속도 - 마찰력
	if (Velocity.Size() <= Friction.Size())
		Velocity = float4::Zero;
	else
		Velocity += Friction;
}

void RigidBody::LimitSpeed()
{
	//X축 최대속도 제한
	float NowSpeedX = abs(Velocity.x);
	float MaxSpeedX = abs(MaxVelocity.x);
	if (MaxSpeedX < NowSpeedX)
	{
		//방향은 그대로, 속도만 MaxSpeed로
		Velocity.x = (Velocity.x / NowSpeedX) * MaxSpeedX;
	}

	//Y축 최대속도 제한
	float NowSpeedY = abs(Velocity.y);
	float MaxSpeedY = abs(MaxVelocity.y);
	if (MaxSpeedY < NowSpeedY)
	{
		//방향은 그대로, 속도만 MaxSpeed로
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
