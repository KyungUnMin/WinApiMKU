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
		MsgAssert("BubbleDestination 클래스는 RoundLevelBase를 상속받은 Level에서만 생성할 수 있습니다");
	}
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

	//화살표 그리기는 나중에 시간 남으면 하자

	//if (NowPos == NextPos)
	//{
	//	MsgAssert("두 벡터가 동일한 위치에 있어 해당 방향벡터의 정규화를 할 수 없습니다");
	//	return;
	//}

	//float4 Dir = NowPos - NextPos;
	//Dir.Normalize();

	////위에서 그린 직선의 벡터와 float4::Right 벡터의 내적 / 두 벡터의 크기
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
