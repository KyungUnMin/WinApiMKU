#include "BubbleDestination.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"

const float4 BubbleDestination::CollisionScale = float4{ 10.f, 10.f };

BubbleDestination::BubbleDestination()
{

}

BubbleDestination::~BubbleDestination()
{

}



void BubbleDestination::Start()
{
	CollisionPtr = CreateCollision(CollisionOrder::BubbleDest);
	CollisionPtr->SetScale(CollisionScale);
}


void BubbleDestination::SetNextDest(BubbleDestination* _Next)
{
	if (this == _Next)
	{
		MsgAssert("다음경로를 자기자신으로 설정할 수는 없습니다");
		return;
	}

	if (nullptr != NextDest)
	{
		MsgAssert("현재 노드는 이미 다음 경로가 지정되어 있습니다");
		return;
	}

	NextDest = _Next;
}


void BubbleDestination::Render(float _DeltaTime)
{
	if (nullptr == NextDest)
		return;

	HDC Hdc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 NowPos = GetPos();
	float4 NextPos = NextDest->GetPos();

	MoveToEx(Hdc, NowPos.ix(), NowPos.iy(), nullptr);
	LineTo(Hdc, NextPos.ix(), NextPos.iy());
}
