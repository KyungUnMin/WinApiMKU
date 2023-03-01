#pragma once
#include "NatureMissleBase.h"

class NatureMissle_Fire : public NatureMissleBase
{
public:
	static const std::string_view ImagePath;
	static const float4 FallColScale;
	static const std::string_view AniNames[3];

	NatureMissle_Fire();
	~NatureMissle_Fire() override;

	NatureMissle_Fire(const NatureMissle_Fire& _Other) = delete;
	NatureMissle_Fire(NatureMissle_Fire&& _Other) noexcept = delete;
	NatureMissle_Fire& operator=(const NatureMissle_Fire& _Other) = delete;
	NatureMissle_Fire& operator=(const NatureMissle_Fire&& _Other) noexcept = delete;

	static void BurnTimeReset()
	{
		PrevPlayerColTime = 0.f;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static float		PrevPlayerColTime;
	const float		InvalidPlayerColTime = 1.5f;

	enum State
	{
		Fall,
		Burn,
		Extinguish
	};

	State				NowState				= State::Fall;
	const float4	FallSpeed				= float4{ 0.f, 300.f };
	const float		ExtinguishTime	= 5.f;
	float				BurnTimer			= 0.f;



	void ResourceLoad();
	void CreateAnimation();

	void Update_Fall(float _DeltaTime);
	void Update_Burn(float _DeltaTime);
	void Update_Extinguish(float _DeltaTime);

	void ChangeState(State _NextState);
	void CollisionCheck();
};

