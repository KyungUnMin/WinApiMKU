#pragma once
#include <GameEngineBase/GameEngineMath.h>

class RoundLevelBase;
class GameEngineActor;
class GamaEngineCollision;

class Gravity
{
public:
	Gravity();
	~Gravity();

	Gravity(const Gravity& _Other) = delete;
	Gravity(Gravity&& _Other) noexcept = delete;
	Gravity& operator=(const Gravity& _Other) = delete;
	Gravity& operator=(const Gravity&& _Other) noexcept = delete;

	void Start(GameEngineActor* _Owner, const float4& _CollisionScale);
	void Update(float _DeltaTime);
	void DebugRender();

	inline float GetAcc()
	{
		return NowGravityAcc;
	}

	inline void SetAcc(float _Acc)
	{
		NowGravityAcc = _Acc;
	}

	void On();
	void Off();

protected:

private:
	bool									UseGravity			= true;

	//�� �浹�� Ȯ���ϱ� ���� ������
	RoundLevelBase*			RoundLevel			= nullptr;
	GameEngineActor*			Owner					= nullptr;
	GamaEngineCollision*		OwnerCollision	= nullptr;

	float4								CollisionScale		= float4::Zero;

	const float						GravityCoef		= 600.0f;

	//���� �������� �߷°��ӵ�
	float								NowGravityAcc = 0.f;

	//���� �������� �߷°��ӵ�
	float								PrevGravityAcc	= 0.0f;

	//�������� Stage�� Collision�� ��Ҵ��� ����
	bool									IsTouchCollision	= false;
};

