#pragma once
#include "ItemBase.h"

enum class BubbleLiquidType
{
	Electronic,
	RainBow,
	Windy,
};

class Item_BubbleLiquid : public ItemBase
{
public:
	Item_BubbleLiquid();
	~Item_BubbleLiquid() override;

	Item_BubbleLiquid(const Item_BubbleLiquid& _Other) = delete;
	Item_BubbleLiquid(Item_BubbleLiquid&& _Other) noexcept = delete;
	Item_BubbleLiquid& operator=(const Item_BubbleLiquid& _Other) = delete;
	Item_BubbleLiquid& operator=(const Item_BubbleLiquid&& _Other) noexcept = delete;

	void InitType(BubbleLiquidType _Type);

protected:
	void Start() override;
	void Excute() override;

private:
	BubbleLiquidType LiquidType = BubbleLiquidType::Electronic;
};

