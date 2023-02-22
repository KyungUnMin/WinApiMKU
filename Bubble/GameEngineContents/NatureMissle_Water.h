#pragma once
#include "NatureMissleBase.h"

class NatureMissle_Water : public NatureMissleBase
{
public:
	static const std::string_view ImagePath;

	NatureMissle_Water();
	~NatureMissle_Water() override;

	NatureMissle_Water(const NatureMissle_Water& _Other) = delete;
	NatureMissle_Water(NatureMissle_Water&& _Other) noexcept = delete;
	NatureMissle_Water& operator=(const NatureMissle_Water& _Other) = delete;
	NatureMissle_Water& operator=(const NatureMissle_Water&& _Other) noexcept = delete;

	inline void InitPos(const float4& _StartPos)
	{
		StartPos = _StartPos;
		SetPos(_StartPos);
	}

	void SetCreateCount(int _Count) 
	{
		WaterCount = _Count;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime)  override;

private:
	const float						ScreenOutOffsetY	= 200.f;
	const float4					MoveSpeed				= { 500.f, 500.f };

	const float						CreateChildTime		= 0.05f;
	float4								StartPos					= float4::Zero;
	int									WaterCount				= 0;


	void ResourceLoad();
	void Move(float _DeltaTime);
	void SetImageFrame();
};

