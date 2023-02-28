#include "Item_Normal.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "RoundLevelBase.h"
#include "PointEffect.h"

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
		MsgAssert("�������� RoundLevel�� �ƴѰ����� �����Ǿ����ϴ�");
		return;
	}

	float4 Pos = _Pos;
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	while (false == RoundLevel->IsBlockPos(Pos))
	{
		Pos += float4::Down;

		if (ScreenSize.y < Pos.y)
		{
			if (true == IsRaisedPos)
			{
				Pos = ScreenSize.half();
				break;
			}

			Pos.y = 50.f;
			IsRaisedPos = true;
		}
	}

	SetPos(Pos);
}



void Item_Normal::Excute()
{
	PointEffect* Point = GetLevel()->CreateActor<PointEffect>(UpdateOrder::PointEffect);
	Point->SetPos(GetPos());
}
