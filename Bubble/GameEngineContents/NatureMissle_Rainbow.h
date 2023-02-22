#pragma once
#include "NatureMissleBase.h"

class NatureMissle_Rainbow : public NatureMissleBase
{
public:
	NatureMissle_Rainbow();
	~NatureMissle_Rainbow() override;

	NatureMissle_Rainbow(const NatureMissle_Rainbow& _Other) = delete;
	NatureMissle_Rainbow(NatureMissle_Rainbow&& _Other) noexcept = delete;
	NatureMissle_Rainbow& operator=(const NatureMissle_Rainbow& _Other) = delete;
	NatureMissle_Rainbow& operator=(const NatureMissle_Rainbow&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	enum class State
	{
		Making,
		Falling,
	};



	void ResourceLoad();
	void CreateAnimation();


};

