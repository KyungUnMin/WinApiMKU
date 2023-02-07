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
		MsgAssert("������θ� �ڱ��ڽ����� ������ ���� �����ϴ�");
		return;
	}

	if (nullptr != NextDest)
	{
		MsgAssert("���� ���� �̹� ���� ��ΰ� �����Ǿ� �ֽ��ϴ�");
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
