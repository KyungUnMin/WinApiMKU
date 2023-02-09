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



	//바로 속도 부여(갑자기 튀어나감)
	inline void SetVelocity(const float4& _Velocity)
	{
		Velocity = _Velocity;
	}

	inline float4 GetVelocity()
	{
		return Velocity;
	}

	//속도 추가(천천히 이동하게 됨, 또는 기존 속도에 방향 전환)
	inline void AddVelocity(const float4& _Velocity)
	{
		Velocity += _Velocity;
	}

	//추가가속도 지정
	inline void SetAccelAlpha(const float4 _AddAccel)
	{
		AccelAlpha = _AddAccel;
	}


	//최대속도 지정
	inline void SetMaxVelocity(const float4& _MaxVelocity)
	{
		MaxVelocity = _MaxVelocity;
	}

	//마찰계수 지정
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

