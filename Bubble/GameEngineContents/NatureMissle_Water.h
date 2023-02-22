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

	void InitPos(const float4& _HeadPos);

protected:
	void Start() override;
	void Update(float _DeltaTime)  override;

private:
	static std::list<NatureMissle_Water*> AllWaters;

	const float						ScreenOutOffsetY	= 200.f;
	const float4					MoveSpeed				= { 500.f, 500.f };

	//const float						TailMoveTime			= 0.005f;
	NatureMissle_Water*		FrontWater				= nullptr;
	float4								PrevPos					= float4::Zero;

	void ResourceLoad();

	void HeadMove(float _DeltaTime);
	void TailMove(float _DeltaTime);

	inline const float4& GetPrevPos()
	{
		return PrevPos;
	}

	void SetImageFrame();
};

