#include "BubbleDestination.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include "BubbleCore.h"
#include "RoundLevelBase.h"

const float4 BubbleDestination::CollisionScale = float4{ 10.f, 10.f };

BubbleDestination::BubbleDestination()
{
	PathLinePen = static_cast<HPEN>(CreatePen(PS_SOLID, 5, RGB(255, 0, 0)));
}

BubbleDestination::~BubbleDestination()
{
	DeleteObject(PathLinePen);
}


void BubbleDestination::Start()
{
	CollisionPtr = CreateCollision(CollisionOrder::BubbleDest);
	CollisionPtr->SetScale(CollisionScale);

	RoundLevel = dynamic_cast<RoundLevelBase*>(GetLevel());
	if (nullptr == RoundLevel)
	{
		MsgAssert("BubbleDestination 클래스는 RoundLevelBase를 상속받은 Level에서만 생성할 수 있습니다");
	}
}


void BubbleDestination::SetNextDest(BubbleDestination* _Next, bool _IsTeleport)
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

	IsTeleport = _IsTeleport;
	NextDest = _Next;
}


void BubbleDestination::Render(float _DeltaTime)
{
	if (false == BubbleCore::GetInst().IsDebug())
		return;

	if (RoundLevel->GetNowStage() != StageIndex)
		return;

	if (nullptr == NextDest)
		return;

	HDC Hdc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	PathLinePen = static_cast<HPEN>(SelectObject(Hdc, PathLinePen));

	float4 NowPos = GetPos();
	float4 NextPos = NextDest->GetPos();

	float4 Dir = NextPos - NowPos;
	float Size = Dir.Size();
	Dir.Normalize();
	NextPos = NowPos + (Dir * (Size * 0.9f));

	MoveToEx(Hdc, NowPos.ix(), NowPos.iy(), nullptr);
	LineTo(Hdc, NextPos.ix(), NextPos.iy());


	if (NowPos == NextPos)
	{
		MsgAssert("두 벡터가 동일한 위치에 있어 해당 방향벡터의 정규화를 할 수 없습니다");
		return;
	}


	//NextPos를 중심으로 회전 45도 회전
	const float Radian = GameEngineMath::PIE / 4;
	const float ArrowLength = 30.f;
	Dir = -Dir;

	{
		float4 LeftArrow;

		LeftArrow.x = (Dir.x * cos(Radian)) - (Dir.y * sin(Radian));
		LeftArrow.y = (Dir.x * sin(Radian)) + (Dir.y * cos(Radian));
		float4 Dest = NextPos + LeftArrow * ArrowLength;

		MoveToEx(Hdc, NextPos.ix(), NextPos.iy(), nullptr);
		LineTo(Hdc, Dest.ix(), Dest.iy());
	}

	{
		float4 RightArrow;

		RightArrow.x = (Dir.x * cos(-Radian)) - (Dir.y * sin(-Radian));
		RightArrow.y = (Dir.x * sin(-Radian)) + (Dir.y * cos(-Radian));
		float4 Dest = NextPos + RightArrow * ArrowLength;

		MoveToEx(Hdc, NextPos.ix(), NextPos.iy(), nullptr);
		LineTo(Hdc, Dest.ix(), Dest.iy());
	}

	PathLinePen = static_cast<HPEN>(SelectObject(Hdc, PathLinePen));
}
