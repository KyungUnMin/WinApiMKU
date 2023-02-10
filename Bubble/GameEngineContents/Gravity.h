#pragma once

class RoundLevelBase;
class GameEngineActor;

class Gravity
{
public:
	Gravity();
	~Gravity();

	Gravity(const Gravity& _Other) = delete;
	Gravity(Gravity&& _Other) noexcept = delete;
	Gravity& operator=(const Gravity& _Other) = delete;
	Gravity& operator=(const Gravity&& _Other) noexcept = delete;

	void Start(GameEngineActor* _Owner);
	void Update(float _DeltaTime);

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
	bool								UseGravity			= true;

	//�� �浹�� Ȯ���ϱ� ���� ������
	RoundLevelBase*		RoundLevel			= nullptr;
	GameEngineActor*		Owner					= nullptr;

	const float					GravityCoef		= 600.0f;

	//���� �������� �߷°��ӵ�
	float							NowGravityAcc = 0.f;

	//���� �������� �߷°��ӵ�
	float							PrevGravityAcc	= 0.0f;

	//�������� Stage�� Collision�� ��Ҵ��� ����
	bool								IsTouchCollision	= false;
};

