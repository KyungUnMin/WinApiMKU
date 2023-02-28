#pragma once
#include "Item_GravityNormal.h"

class Item_BossJewellery : public Item_GravityNormal
{
public:
	static const std::string_view ImagePath;

	Item_BossJewellery();
	~Item_BossJewellery();

	Item_BossJewellery(const Item_BossJewellery& _Other) = delete;
	Item_BossJewellery(Item_BossJewellery&& _Other) noexcept = delete;
	Item_BossJewellery& operator=(const Item_BossJewellery& _Other) = delete;
	Item_BossJewellery& operator=(const Item_BossJewellery&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	const	float4 RenderScale		= float4{ 400.f, 400.f };
	const	float4 StartSpeed		= float4{ 0.f, -450.f };

	void ResourceLoad();
	void CreateAnimation();
};

