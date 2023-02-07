#include "BubbleDestination.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include "BubbleCore.h"
#include "RoundLevelBase.h"

const float4 BubbleDestination::CollisionScale = float4{ 100.f, 100.f };

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

	MoveToEx(Hdc, NowPos.ix(), NowPos.iy(), nullptr);
	LineTo(Hdc, NextPos.ix(), NextPos.iy());

	//ȭ��ǥ �׸���� ���߿� �ð� ������ ����

	//if (NowPos == NextPos)
	//{
	//	MsgAssert("�� ���Ͱ� ������ ��ġ�� �־� �ش� ���⺤���� ����ȭ�� �� �� �����ϴ�");
	//	return;
	//}

	//float4 Dir = NowPos - NextPos;
	//Dir.Normalize();

	////������ �׸� ������ ���Ϳ� float4::Right ������ ���� / �� ������ ũ��
	//float NowRadian = Dir.x / Dir.Size();

	//const float RotateRadian = GameEngineMath::PIE * 0.5f;
	//float RightAngle = NowRadian + RotateRadian;
	//float LeftAngle = NowRadian - RotateRadian;


	//const float Length = 20.f;

	//float4 RightArrow = NextPos;
	//RightArrow.x -= Length * cos(RightAngle);
	//RightArrow.y -= Length * sin(RightAngle);

	//float4 LeftArrow = NextPos;
	//LeftArrow.x += Length * static_cast<float>(cos(LeftAngle));
	//LeftArrow.y -= Length * static_cast<float>(sin(LeftAngle));


	//MoveToEx(Hdc, NextPos.ix(), NextPos.iy(), nullptr);
	//LineTo(Hdc, RightArrow.ix(), RightArrow.iy());
	//MoveToEx(Hdc, NextPos.ix(), NextPos.iy(), nullptr);
	//LineTo(Hdc, LeftArrow.ix(), LeftArrow.iy());


	PathLinePen = static_cast<HPEN>(SelectObject(Hdc, PathLinePen));
}
