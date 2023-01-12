#pragma once
#include <Windows.h>
#include <string_view>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <vector>

struct ImageCutData
{
	float StartX = 0.0f;
	float StartY = 0.0f;
	float SizeX = 0.0f;
	float SizeY = 0.0f;

	float4 GetStartPos()
	{
		return { StartX, StartY };
	}

	float4 GetScale()
	{
		return { SizeX, SizeY };
	}
};

class GameEnginePath;

class GameEngineImage
{
public:
	GameEngineImage();
	~GameEngineImage();

	GameEngineImage(const GameEngineImage& _Other) = delete;
	GameEngineImage(GameEngineImage&& _Other) noexcept = delete;
	GameEngineImage& operator=(const GameEngineImage& _Other) = delete;
	GameEngineImage& operator=(const GameEngineImage&& _Other) noexcept = delete;

	//���� HDC�� ���� �� ������ ���� �ʱ�ȭ
	bool ImageCreate(HDC _Hdc);

	//ũ�⸦ �Է¹޾Ƽ� BitMap�� ����� ImageDC�� ���� �� ���� �ʱ�ȭ
	bool ImageCreate(const float4 _Scale);

	//ImageLoad(const std::string_view& _Path)�� ����
	bool ImageLoad(const GameEnginePath& _Path);

	//string�� �̿��� �̹��� �ε�
	bool ImageLoad(const std::string_view& _Path);

	//�̹����� ������� ĥ�ع�����
	void ImageClear();

	HDC GetImageDC() const
	{
		return ImageDC;
	}

	//X(���� �̹��� ����), Y(���� �̹��� ����)�� �ڸ� �̹��� ������ ���Ϳ� ����
	void Cut(int _X, int _Y);

	float4 GetImageScale() const
	{
		return float4{ static_cast<float>(Info.bmWidth), static_cast<float>(Info.bmHeight) };
	}

	//�߸� �̹������� Ȯ��
	bool IsImageCutting() const
	{
		return IsCut;
	}

	//���;ȿ� ��ȿ�� �������� Ȯ��
	bool IsCutIndexValid(int _Index) const
	{
		if (_Index < 0)
			return false;

		if (ImageCutDatas.size() <= _Index)
			return false;

		return true;
	}

	//���ϴ� �ε����� �̹��� ���� ��������
	ImageCutData GetCutData(int _Index) const
	{
		if (false == IsCutIndexValid(_Index))
		{
			MsgAssert("��ȿ���� ���� �� �ε���");
			return ImageCutData();
		}

		return ImageCutDatas[_Index];
	}

	//���ڷ� ���� �̹��� ��ü�� �� ��ü�� HDC�� bitblt
	void BitCopy(
		GameEngineImage* _OtherImage, 
		float4 _Pos, float4 _Scale);

	//���õ� �̹��� TransParentBlt
	void TransCopy(
		const GameEngineImage* _OtherImage,
		int _CutIndex,
		float4 _OtherCenterPos, float4 _OtherCenterSize,
		int _Color = RGB(147, 187, 236));

	//���ڷ� ���� �̹����� ���� ��ü�� TransParentBlt
	void TransCopy(
		const GameEngineImage* _OtherImage, 
		float4 _CopyCenterPos, float4 _CopySize, 
		float4 _OtherImagePos, float4 _OtherImageSize, 
		int _Color = RGB(147, 187, 236));

protected:

private:
	HDC				ImageDC			= nullptr;
	HBITMAP		BitMap				= nullptr;
	HBITMAP		OldBitMap		= nullptr;
	BITMAP		Info					= BITMAP();
	bool				IsCut				= false;

	//Ŀ���� �̹��� �������� ����
	std::vector<ImageCutData> ImageCutDatas;

	//���� BITMAP�� ������ Info�� ����ϴ� �Լ� 
	void ImageScaleCheck();
};

