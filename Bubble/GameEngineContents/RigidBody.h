#pragma once
#include <GameEngineBase/GameEngineMath.h>

class GameEngineActor;

class RigidBody
{
public:
	RigidBody();
	~RigidBody();

	RigidBody(const RigidBody& _Other) = delete;
	RigidBody(RigidBody&& _Other) noexcept = delete;
	RigidBody& operator=(const RigidBody& _Other) = delete;
	RigidBody& operator=(const RigidBody&& _Other) noexcept = delete;

	void Update(float _DeltaTime);

	void SetOwner(GameEngineActor* _Actor)
	{
		Owner = _Actor;
	}

	inline void AddForce(const float4& _Force)
	{
		ForceVec += _Force;
	}

	inline void SetMass(float _Mass)
	{
		Mass = _Mass;
	}



	//�ٷ� �ӵ� �ο�(���ڱ� Ƣ���)
	inline void SetVelocity(const float4& _Velocity)
	{
		Velocity = _Velocity;
	}

	inline float4 GetVelocity()
	{
		return Velocity;
	}

	//�ӵ� �߰�(õõ�� �̵��ϰ� ��, �Ǵ� ���� �ӵ��� ���� ��ȯ)
	inline void AddVelocity(const float4& _Velocity)
	{
		Velocity += _Velocity;
	}

	//�߰����ӵ� ����
	inline void SetAccelAlpha(const float4 _AddAccel)
	{
		AccelAlpha = _AddAccel;
	}


	//�ִ�ӵ� ����
	inline void SetMaxVelocity(const float4& _MaxVelocity)
	{
		MaxVelocity = _MaxVelocity;
	}

	//������� ����
	inline void SetFricion(float _FricCoef)
	{
		FricCoef = _FricCoef;
	}
	

protected:

private:
	GameEngineActor*	Owner				= nullptr;

	float4						ForceVec			= float4::Zero;
	float4						Acceleration	= float4::Zero;
	float4						Velocity			= float4::Zero;
	float4						AccelAlpha		= float4::Zero;

	float						Mass				= 1.f;
	float4						MaxVelocity	= float4{ 200.f, 200.f };
	float						FricCoef			= 100.f;

	void CalcForce();
	void CalcFric(float _DeltaTime);
	void LimitSpeed();
	void Move(float _DeltaTime);
};

