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

//���� HDC�� ���� �� ������ ���� �ʱ�ȭ
bool GameEngineImage::ImageCreate(HDC _Hdc)
{
	if (nullptr == _Hdc)
	{
		MsgAssert("�̹��� ������ ����\nnullptr�� HDC�� �־���");
		return false;
	}

	ImageDC = _Hdc;
	ImageScaleCheck();
	return true;
}


//ũ�⸦ �Է¹޾Ƽ� BitMap�� ����� ImageDC�� ���� �� ���� �ʱ�ȭ
bool GameEngineImage::ImageCreate(const float4 _Scale)
{
	if (true == _Scale.IsZero())
	{
		MsgAssert("ũ�Ⱑ 0�� �̹����� ���� ���� ����");
		return false;
	}

	BitMap = CreateCompatibleBitmap(GameEngineWindow::GetWindowBackBufferHdc(), _Scale.ix(), _Scale.iy());
	if (nullptr == BitMap)
	{
		MsgAssert("�̹��� ��Ʈ�� ������ ����");
		return false;
	}

	ImageDC = CreateCompatibleDC(nullptr);
	if (nullptr == ImageDC)
	{
		MsgAssert("�̹��� HDC ������ ����");
		return false;
	}

	//��� ���� ��Ʈ�ʰ� ��� ���� DC�� 1�ȼ� ��Ʈ���� ��ȯ
	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	//ũ�� ����
	ImageScaleCheck();

	//��Ʈ�� ������� ä���
	ImageClear();

	return true;
}



//ImageLoad(const std::string_view& _Path)�� ����
bool GameEngineImage::ImageLoad(const GameEnginePath& _Path)
{
	return ImageLoad(_Path.GetPathToString().c_str());
}

//string�� �̿��� �̹��� �ε�
bool GameEngineImage::ImageLoad(const std::string_view& _Path)
{
	BitMap = static_cast<HBITMAP>(LoadImageA(nullptr, _Path.data(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	if (nullptr == BitMap)
	{
		std::string Path = _Path.data();
		MsgAssert(Path + " : �̹��� �ε忡 ����");
		return false;
	}

	ImageDC = CreateCompatibleDC(nullptr);
	if (nullptr == ImageDC)
	{
		std::string Path = _Path.data();
		MsgAssert(Path + " �̹��� HDC ������ ����");
		return false;
	}

	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));
	ImageScaleCheck();
	return true;
}


//�̹����� ������� ĥ�ع�����
void GameEngineImage::ImageClear()
{
	Rectangle(ImageDC, -1, -1, Info.bmWidth + 1, Info.bmHeight + 1);
}

//X(���� �̹��� ����), Y(���� �̹��� ����)�� �ڸ� �̹��� ������ ���Ϳ� ����
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

//���� BITMAP�� ������ Info�� ����ϴ� �Լ� 
void GameEngineImage::ImageScaleCheck()
{
	HBITMAP CurrentBitMap = static_cast<HBITMAP>(GetCurrentObject(ImageDC, OBJ_BITMAP));
	GetObject(CurrentBitMap, sizeof(BITMAP), &Info);
}

//���ڷ� ���� �̹��� ��ü�� �� ��ü�� HDC�� ����
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
		MsgAssert("�߸��� ���� �̹����� Cut��� �Լ� ���");
		return;
	}

	ImageCutData Data = _OtherImage->GetCutData(_CutIndex);
	TransCopy(_OtherImage, _OtherCenterPos, _OtherCenterSize, Data.GetStartPos(), Data.GetScale(), _Color);
}

//���ڷ� ���� �̹����� ���� ��ü�� TransParentBlt
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
