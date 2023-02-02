#pragma once
#include "ComponentBase.h"

class RoundLevelBase;
class MovableActor;

//MovableActor이 존재하는 객체의 중력을 담당함
class Gravity : public ComponentBase
{
public:
	static bool GlobalGravityUse;

	Gravity();
	~Gravity();

	Gravity(const Gravity& _Other) = delete;
	Gravity(Gravity&& _Other) noexcept = delete;
	Gravity& operator=(const Gravity& _Other) = delete;
	Gravity& operator=(const Gravity&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	//맵 충돌을 확인하기 위한 포인터
	RoundLevelBase*		RoundLevel			= nullptr;
	MovableActor*			MovableOwner	= nullptr;

	const float					GravityCoef		= 600.0f;

	//이전 프레임의 중력가속도
	float							PrevGravityAcc	= 0.0f;

	//점프에서 Stage의 Collision에 닿았는지 여부
	bool								IsTouchCollision	= false;
};

