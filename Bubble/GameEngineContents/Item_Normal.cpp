#include "Item_Normal.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineRender.h>

Item_Normal::Item_Normal()
{

}

Item_Normal::~Item_Normal()
{

}

void Item_Normal::Start()
{
	ItemBase::Start();

	GameEngineRender* RenderPtr = GetRender();
	RenderPtr->SetImage(ItemBase::NormalImgPath);

	int RandomIndex = GameEngineRandom::MainRandom.RandomInt(0, 89);
	RenderPtr->SetFrame(RandomIndex);
}

void Item_Normal::Excute()
{

}
