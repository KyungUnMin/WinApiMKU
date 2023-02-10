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

	//맵 충돌을 확인하기 위한 포인터
	RoundLevelBase*		RoundLevel			= nullptr;
	GameEngineActor*		Owner					= nullptr;

	const float					GravityCoef		= 600.0f;

	//현재 프레임의 중력가속도
	float							NowGravityAcc = 0.f;

	//이전 프레임의 중력가속도
	float							PrevGravityAcc	= 0.0f;

	//점프에서 Stage의 Collision에 닿았는지 여부
	bool								IsTouchCollision	= false;
};

