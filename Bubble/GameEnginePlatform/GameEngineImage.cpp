#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#pragma comment(lib, "msimg32.lib")

GameEngineImage::GameEngineImage()
{

}

GameEngineImage::~GameEngineImage()
{
	if (nullptr != BitMap)
	{
		DeleteObject(BitMap);
		BitMap = nullptr;
	}

	if (nullptr != OldBitMap)
	{
		DeleteObject(OldBitMap);
		OldBitMap = nullptr;
	}

	if (nullptr != ImageDC)
	{
		DeleteDC(ImageDC);
		ImageDC = nullptr;
	}
}

//인자 HDC와 연결 및 사이즈 정보 초기화
bool GameEngineImage::ImageCreate(HDC _Hdc)
{
	if (nullptr == _Hdc)
	{
		MsgAssert("이미지 생성에 실패\nnullptr인 HDC를 넣어줌");
		return false;
	}

	ImageDC = _Hdc;
	ImageScaleCheck();
	return true;
}


//크기를 입력받아서 BitMap을 만들고 ImageDC에 연결 및 정보 초기화
bool GameEngineImage::ImageCreate(const float4 _Scale)
{
	if (true == _Scale.IsZero())
	{
		MsgAssert("크기가 0인 이미지를 만들 수는 없음");
		return false;
	}

	BitMap = CreateCompatibleBitmap(GameEngineWindow::GetWindowBackBufferHdc(), _Scale.ix(), _Scale.iy());
	if (nullptr == BitMap)
	{
		MsgAssert("이미지 비트맵 생성에 실패");
		return false;
	}

	ImageDC = CreateCompatibleDC(nullptr);
	if (nullptr == ImageDC)
	{
		MsgAssert("이미지 HDC 생성에 실패");
		return false;
	}

	//방금 만든 비트맵과 방금 만든 DC의 1픽셀 비트맵을 교환
	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	//크기 측정
	ImageScaleCheck();

	//비트맵 흰색으로 채우기
	ImageClear();

	return true;
}



//ImageLoad(const std::string_view& _Path)를 래핑
bool GameEngineImage::ImageLoad(const GameEnginePath& _Path)
{
	return ImageLoad(_Path.GetPathToString().c_str());
}

//string을 이용한 이미지 로드
bool GameEngineImage::ImageLoad(const std::string_view& _Path)
{
	BitMap = static_cast<HBITMAP>(LoadImageA(nullptr, _Path.data(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	if (nullptr == BitMap)
	{
		std::string Path = _Path.data();
		MsgAssert(Path + " : 이미지 로드에 실패");
		return false;
	}

	ImageDC = CreateCompatibleDC(nullptr);
	if (nullptr == ImageDC)
	{
		std::string Path = _Path.data();
		MsgAssert(Path + " 이미지 HDC 생성에 실패");
		return false;
	}

	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));
	ImageScaleCheck();
	return true;
}


//이미지를 흰색으로 칠해버리기
void GameEngineImage::ImageClear()
{
	Rectangle(ImageDC, -1, -1, Info.bmWidth + 1, Info.bmHeight + 1);
}

//X(가로 이미지 갯수), Y(세로 이미지 갯수)로 자른 이미지 정보를 벡터에 저장
void GameEngineImage::Cut(int _X, int _Y)
{
	ImageCutDatas.reserve(_X * _Y);

	ImageCutData Data;
	Data.SizeX = static_cast<float>(GetImageScale().ix() / _X);
	Data.SizeY = static_cast<float>(GetImageScale().iy() / _Y);

	for (size_t i = 0; i < _Y; ++i)
	{
		for (size_t j = 0; j < _X; ++j)
		{
			ImageCutDatas.push_back(Data);
			Data.StartX += Data.SizeX;
		}

		Data.StartX = 0.0f;
		Data.StartY+= Data.SizeY;
	}

	IsCut = true;
}

//현재 BITMAP의 정보를 Info로 기록하는 함수 
void GameEngineImage::ImageScaleCheck()
{
	HBITMAP CurrentBitMap = static_cast<HBITMAP>(GetCurrentObject(ImageDC, OBJ_BITMAP));
	GetObject(CurrentBitMap, sizeof(BITMAP), &Info);
}

//인자로 받은 이미지 전체를 이 객체의 HDC에 복사
void GameEngineImage::BitCopy(GameEngineImage* _OtherImage, float4 _Pos, float4 _Scale)
{
	BitBlt(
		ImageDC,
		_Pos.ix() - _Scale.hix(),
		_Pos.iy() - _Scale.hiy(),
		_Scale.ix(),
		_Scale.iy(),
		_OtherImage->GetImageDC(), 
		0,
		0,
		SRCCOPY
	);
}

void GameEngineImage::TransCopy(
	const GameEngineImage* _OtherImage, int _CutIndex, 
	float4 _OtherCenterPos, float4 _OtherCenterSize, 
	int _Color)
{
	if (false == _OtherImage->IsCut)
	{
		MsgAssert("잘리지 않은 이미지로 Cut출력 함수 사용");
		return;
	}

	ImageCutData Data = _OtherImage->GetCutData(_CutIndex);
	TransCopy(_OtherImage, _OtherCenterPos, _OtherCenterSize, Data.GetStartPos(), Data.GetScale(), _Color);
}

//인자로 받은 이미지를 현재 객체에 TransParentBlt
void GameEngineImage::TransCopy(
	const GameEngineImage* _OtherImage, 
	float4 _CopyCenterPos, float4 _CopySize, 
	float4 _OtherImagePos, float4 _OtherImageSize, 
	int _Color)
{
	TransparentBlt(ImageDC,
		_CopyCenterPos.ix() - _CopySize.hix(),
		_CopyCenterPos.iy() - _CopySize.hiy(),
		_CopySize.ix(),
		_CopySize.iy(),
		_OtherImage->GetImageDC(),
		_OtherImagePos.ix(),
		_OtherImagePos.iy(),
		_OtherImageSize.ix(),
		_OtherImageSize.iy(),
		_Color);
}
