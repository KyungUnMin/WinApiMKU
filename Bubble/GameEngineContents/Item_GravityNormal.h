#pragma once
#include "Item_Normal.h"

class RoundLevelBase;

class Item_GravityNormal : public Item_Normal
{
public:
	Item_GravityNormal();
	~Item_GravityNormal() override;

	Item_GravityNormal(const Item_GravityNormal& _Other) = delete;
	Item_GravityNormal(Item_GravityNormal&& _Other) noexcept = delete;
	Item_GravityNormal& operator=(const Item_GravityNormal& _Other) = delete;
	Item_GravityNormal& operator=(const Item_GravityNormal&& _Other) noexcept = delete;

	void Init(const float4& _Pos) override {}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	inline void SetStartSpeed(const float4& _Speed)
	{
		NowSpeed = _Speed;
	}

	void ConnectRoundLevel();

private:
	RoundLevelBase*	RoundLevel = nullptr;
	float4						NowSpeed	= float4::Zero;
	const float				GravityAcc	= 200.f;
	bool							IsLand			= false;
};

