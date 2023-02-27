#pragma once
#include "NatureMissleBase.h"

class NatureMissle_Rainbow : public NatureMissleBase
{
public:
	static const std::string_view ImagePath;
	static const float4 CollisionScale;
	static const float4 CollisionOffset;
	static const float4 RenderScale;

	NatureMissle_Rainbow();
	~NatureMissle_Rainbow() override;

	NatureMissle_Rainbow(const NatureMissle_Rainbow& _Other) = delete;
	NatureMissle_Rainbow(NatureMissle_Rainbow&& _Other) noexcept = delete;
	NatureMissle_Rainbow& operator=(const NatureMissle_Rainbow& _Other) = delete;
	NatureMissle_Rainbow& operator=(const NatureMissle_Rainbow&& _Other) noexcept = delete;

	void DestroyByBoss() override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	const float4	MoveSpeed				= float4{ 0.f, 500.f };
	const float4	ScreenOutOffset	= float4{ 0.f, 50.f };

	void LoadSFX();
	void ResourceLoad();
	void CreateAnimation();
};

