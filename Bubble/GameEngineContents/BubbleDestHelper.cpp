#include "BubbleDestHelper.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"
#include "BubbleDestination.h"

bool				BubbleDestHelper::IsRenderOn		= false;
const int		BubbleDestHelper::WidthCount		= 32;
const int		BubbleDestHelper::HeightCount	= 24;

float4 BubbleDestHelper::GetGridPos(int _Index)
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	int X = _Index % WidthCount;
	int Y = _Index / WidthCount;

	float4 PixelSize = { (ScreenSize.x / WidthCount), (ScreenSize.y / HeightCount) };
	float4 Pos = float4{ (PixelSize.x * X), (PixelSize.y * Y) };
	return Pos;
}

BubbleDestHelper::BubbleDestHelper()
{
	GridPen = static_cast<HPEN>(CreatePen(PS_DOT, 1, RGB(0, 0, 0)));
}

BubbleDestHelper::~BubbleDestHelper()
{
	DeleteObject(GridPen);
}



void BubbleDestHelper::Start()
{
	ScreenSize = GameEngineWindow::GetScreenSize();
}

void BubbleDestHelper::Render(float _DeltaTime)
{
	if (false == IsRenderOn)
		return;

	HDC Hdc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	GridPen = static_cast<HPEN>(SelectObject(Hdc, GridPen));
	DWORD DefaultColor = SetTextColor(Hdc, RGB(0, 0, 0));
	SetBkMode(Hdc, TRANSPARENT);

	for (int y = 0; y < HeightCount; ++y)
	{
		int CurY = (ScreenSize.iy() / HeightCount) * y;
		CurY += Offset.iy();

		MoveToEx(Hdc, 0, CurY, nullptr);
		LineTo(Hdc, ScreenSize.ix(), CurY);

		for (int x = 0; x < WidthCount; ++x)
		{
			int CurX = (ScreenSize.ix() / WidthCount) * x;
			CurX += Offset.ix();

			if (1 == y)
			{
				MoveToEx(Hdc, CurX, 0, nullptr);
				LineTo(Hdc, CurX, ScreenSize.iy());
			}

			int PixelIndex = y * WidthCount + x;
			std::string StrIndex = std::to_string(PixelIndex).c_str();
			TextOutA(Hdc, CurX + 1, CurY + 1, StrIndex.c_str(), static_cast<int>(StrIndex.size()));
		}
	}

	GridPen = static_cast<HPEN>(SelectObject(Hdc, GridPen));
	SetTextColor(Hdc, DefaultColor);
	SetBkMode(Hdc, OPAQUE);
}



//enum을 받아 static const std::vector<std::vector<int>>를 반환
const std::vector<std::vector<int>>& BubbleDestHelper::GetData(HelpLevelType _LevelType)
{
	switch (_LevelType)
	{
	case HelpLevelType::RoundAEnter:
		return RoundAEnter;
	case HelpLevelType::RoundA1:
		return RoundA1;
	case HelpLevelType::RoundA2:
		return RoundA2;
	case HelpLevelType::RoundA3:
		return RoundA3;
	}

	assert(nullptr);
	return RoundAEnter;
}


//enum값을 입력받아 BubbleDestination을 생성하고 위치값 설정
void BubbleDestHelper::SetBubbleDest(HelpLevelType _LevelType)
{
	const std::vector<std::vector<int>>& DestDatas = GetData(_LevelType);

	BubbleDests.resize(DestDatas.size());

	for (size_t Stage = 0; Stage < DestDatas.size(); ++Stage)
	{
		BubbleDests[Stage].reserve(DestDatas[Stage].size());
		for (size_t i = 0; i < DestDatas[Stage].size(); ++i)
		{
			BubbleDestination* Dest = GetLevel()->CreateActor<BubbleDestination>(UpdateOrder::BubbleDest);
			Dest->SetStageIndex(Stage);
			float4 Pos = GetPointPos(DestDatas[Stage][i]);
			Dest->SetPos(Pos + Offset);
			BubbleDests[Stage].push_back(Dest);
		}
	}
}

void BubbleDestHelper::SetMoveDestPos(size_t _Stage, size_t _Num, const float4& _Offset)
{
	if (BubbleDests.size() <= _Stage)
	{
		MsgAssert("해당 스테이지는 존재하지 않습니다");
		return;
	}

	if (BubbleDests[_Stage].size() <= _Num)
	{
		MsgAssert("해당 스테이지에는 그 순서에 해당되는 BubbleDest가 존재하지 않습니다");
		return;
	}

	BubbleDests[_Stage][_Num]->SetMove(_Offset);
}



//그리드의 인덱스값을 화면의 좌표로 변경
float4 BubbleDestHelper::GetPointPos(int _Index, const float4& _Offset)
{
	int X = _Index % WidthCount;
	int Y = _Index / WidthCount;

	float4 PixelSize = { (ScreenSize.x / WidthCount), (ScreenSize.y / HeightCount) };
	float4 Pos = float4{ (PixelSize.x * X), (PixelSize.y * Y) };
	return Pos + _Offset;
}


//Dest의 이동경로 설정
void BubbleDestHelper::ConnectDestToDest(size_t _Stage, size_t _Start, size_t _End)
{
	if (BubbleDests.size() <= _Stage)
	{
		MsgAssert("해당 스테이지는 버블의 Dest를 설정해주지 않았습니다");
		return;
	}

	if (BubbleDests[_Stage].size() <= _Start || BubbleDests[_Stage].size() <= _End)
	{
		MsgAssert("BubbleDest들 끼리 연결해줄때 해당 스테이지의 인덱스를 초과하였습니다");
		return;
	}

	BubbleDests[_Stage][_Start]->SetNextDest(BubbleDests[_Stage][_End]);
}

std::vector<BubbleDestination*>& BubbleDestHelper::GetBubbleDest(size_t _Stage)
{
	if (BubbleDests.size() <= _Stage)
	{
		MsgAssert("해당 스테이지는 버블의 Dest를 설정해주지 않았습니다");
	}

	return BubbleDests[_Stage];
}


//지정한 스테이지의 버블 목적지만 켜고 나머지는 끄기
void BubbleDestHelper::TurnOnBubbleDest(size_t _Stage)
{
	for (size_t Stage = 0; Stage < BubbleDests.size(); ++Stage)
	{
		for (size_t i = 0; i < BubbleDests[Stage].size(); ++i)
		{
			if (_Stage == BubbleDests[Stage][i]->GetStageIndex())
			{
				BubbleDests[Stage][i]->On();
			}
			else
			{
				BubbleDests[Stage][i]->Off();
			}
		}
	}


}
