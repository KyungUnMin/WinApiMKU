#pragma once
#include "ItemBase.h"

class Item_Normal : public ItemBase
{
public:
	Item_Normal();
	~Item_Normal();

	Item_Normal(const Item_Normal& _Other) = delete;
	Item_Normal(Item_Normal&& _Other) noexcept = delete;
	Item_Normal& operator=(const Item_Normal& _Other) = delete;
	Item_Normal& operator=(const Item_Normal&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Excute() override;

private:

};

