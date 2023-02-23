#include "Item_Normal.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "RoundLevelBase.h"

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



void Item_Normal::Init(const float4& _Pos)
{
	RoundLevelBase* RoundLevel = dynamic_cast<RoundLevelBase*>(GetLevel());
	if (nullptr == RoundLevel)
	{
		MsgAssert("아이템이 RoundLevel이 아닌곳에서 생성되었습니다");
		return;
	}

	float4 Pos = _Pos;
	float4 ScreenSize = GameEngineWindow::GetScreenSize();


	while (false == RoundLevel->IsBlockPos(Pos))
	{
		Pos += float4::Down;

		if (ScreenSize.y < Pos.y)
		{
			Pos.y = 50.f;
		}
	}

	SetPos(Pos);
}



void Item_Normal::Excute()
{

}
