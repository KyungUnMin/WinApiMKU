#include "Item_BubbleLiquid.h"
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerBase.h"
#include "BubbleSpawner.h"
#include "BubbleSpawner.h"

Item_BubbleLiquid::Item_BubbleLiquid()
{

}

Item_BubbleLiquid::~Item_BubbleLiquid()
{

}



void Item_BubbleLiquid::Start()
{
	ItemBase::Start();

	GameEngineRender* RenderPtr = GetRender();
	RenderPtr->SetImage(ItemBase::BubbleLiquidImgPath);
}

void Item_BubbleLiquid::InitType(BubbleLiquidType _Type)
{
	LiquidType = _Type;
	GameEngineRender* RenderPtr = GetRender();
	RenderPtr->SetFrame(static_cast<int>(LiquidType));
}

void Item_BubbleLiquid::Excute()
{
	BubbleSpawner* PlayerBubbleSpawner = PlayerBase::MainPlayer->GetBubbleSpawner();

	switch (LiquidType)
	{
	case BubbleLiquidType::Electronic:
		PlayerBubbleSpawner->SetBubbleType(BubbleMissleType::Electronic);
		break;
	case BubbleLiquidType::RainBow:
		PlayerBubbleSpawner->SetBubbleType(BubbleMissleType::Rainbow);
		break;
	case BubbleLiquidType::Windy:
		PlayerBubbleSpawner->SetBubbleType(BubbleMissleType::Windy);
		break;
	}
}
