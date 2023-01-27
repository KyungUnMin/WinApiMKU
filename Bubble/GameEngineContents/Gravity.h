#pragma once
#include "ComponentBase.h"

class RoundLevelBase;
class MovableActor;

class Gravity : public ComponentBase
{
public:
	Gravity();
	~Gravity();

	Gravity(const Gravity& _Other) = delete;
	Gravity(Gravity&& _Other) noexcept = delete;
	Gravity& operator=(const Gravity& _Other) = delete;
	Gravity& operator=(const Gravity&& _Other) noexcept = delete;

	//void Jump(float _JumpAcc);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	//�� �浹�� Ȯ���ϱ� ���� ������
	RoundLevelBase*		RoundLevel			= nullptr;
	MovableActor*			MovableOwner	= nullptr;

	const float					GravityCoef		= 200.0f;
};

