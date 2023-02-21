#pragma once
#include "NatureMissleBase.h"

class NatureMissle_Water : public NatureMissleBase
{
public:
	NatureMissle_Water();
	~NatureMissle_Water();

	NatureMissle_Water(const NatureMissle_Water& _Other) = delete;
	NatureMissle_Water(NatureMissle_Water&& _Other) noexcept = delete;
	NatureMissle_Water& operator=(const NatureMissle_Water& _Other) = delete;
	NatureMissle_Water& operator=(const NatureMissle_Water&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime)  override;

private:

};

