#pragma once
#include "ComponentBase.h"

class RoundLevelBase;

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
	RoundLevelBase*		RoundLevel		= nullptr;
	float							Acceleration	= 0.0f;
	const float					GravityAcc		= 200.0f;

};

