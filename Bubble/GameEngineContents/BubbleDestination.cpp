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
		MsgAssert("BubbleDestination Ŭ������ RoundLevelBase�� ��ӹ��� Level������ ������ �� �ֽ��ϴ�");
	}
}


void BubbleDestination::SetNextDest(BubbleDestination* _Next, bool _IsTeleport)
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
		MsgAssert("�� ���Ͱ� ������ ��ġ�� �־� �ش� ���⺤���� ����ȭ�� �� �� �����ϴ�");
		return;
	}


	//NextPos�� �߽����� ȸ�� 45�� ȸ��
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
