#pragma once
#include "ComponentBase.h"

class RoundLevelBase;
class MovableActor;

//MovableActor�� �����ϴ� ��ü�� �߷��� �����
class Gravity : public ComponentBase
{
public:
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
	//�� �浹�� Ȯ���ϱ� ���� ������
	RoundLevelBase*		RoundLevel			= nullptr;
	MovableActor*			MovableOwner	= nullptr;

	const float					GravityCoef		= 300.0f;
};

