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

	virtual void Init(const float4& _Pos);

protected:
	void Start() override;
	void Excute() override;

private:
	bool IsRaisedPos = false;
};

