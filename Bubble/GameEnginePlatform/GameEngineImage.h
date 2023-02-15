#pragma once
#include <Windows.h>
#include <string_view>
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineDebug.h>


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
	GameEngineImage& operator=(GameEngineImage&& _Other) noexcept = delete;



	//���� HDC�� ���� �� ������ ���� �ʱ�ȭ
	bool ImageCreate(HDC _Hdc);

	//ũ�⸦ �Է¹޾Ƽ� BitMap�� ����� ImageDC�� ���� �� ���� �ʱ�ȭ
	bool ImageCreate(const float4& _Scale);

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

	float4 GetImageScale() const
	{
		return float4{ static_cast<float>(Info.bmWidth), static_cast<float>(Info.bmHeight) };
	}



	//�߸� �̹������� Ȯ��
	bool IsImageCutting()
	{
		return IsCut;
	}

	size_t GetImageCuttingCount()
	{
		return ImageCutDatas.size();
	}

	//���;ȿ� ��ȿ�� �������� Ȯ��
	bool IsCutIndexValid(int _Index) const
	{
		if (0 > _Index)
		{
			return false;
		}

		if (ImageCutDatas.size() <= _Index)
		{
			return false;
		}

		return true;
	}

	//���ϴ� �ε����� �̹��� ���� ��������
	ImageCutData GetCutData(int _Index) const
	{
		if (false == IsCutIndexValid(_Index))
		{
			MsgAssert("��ȿ���� ���� �� �ε��� �Դϴ�.");
		}

		return ImageCutDatas[_Index];
	}


	//�̹����� �ڸ� ������, ����, �ڸ� ����(���� ����)
	void Cut(float4 _Start, float4 _End, int _X, int _Y);

	//X(���� �̹��� ����), Y(���� �̹��� ����)�� �ڸ� �̹��� ������ ���Ϳ� ����
	void Cut(int _X, int _Y);


	//���ڷ� ���� �̹��� ��ü�� �� ��ü�� HDC�� bitblt
	void BitCopy(
		const GameEngineImage* _OtherImage,
		float4 _CenterPos, float4 _Scale);


	//���ڷ� ���� �̹����� ���� ��ü�� TransParentBlt
	void TransCopy(
		const GameEngineImage* _OtherImage,
		float4 _CopyCenterPos, float4 _CopySize,
		float4 _OtherImagePos, float4 _OtherImageSize,
		int _Color = RGB(147, 187, 236));


	//���õ� �̹��� TransParentBlt
	void TransCopy(
		const GameEngineImage* _OtherImage, int _CutIndex, 
		float4 _CopyCenterPos, float4 _CopySize, 
		int _Color = RGB(147, 187, 236));


	void AlphaCopy(
		const GameEngineImage* _OtherImage,
		float4 _CopyCenterPos, float4 _CopySize,
		float4 _OtherImagePos, float4 _OtherImageSize,
		int _Alpha);


	void AlphaCopy(
		const GameEngineImage* _OtherImage, int _CutIndex,
		float4 _CopyCenterPos, float4 _CopySize,
		int _Alpha);



	//���� ������ �ִ� �̹������� �ش� ��ǥ�� ������ �޾ƿ�
	DWORD GetPixelColor(float4 _Pos, DWORD _OutColor);

	//���� ������ �ִ� �̹������� �ش� ��ǥ�� ������ �޾ƿ�
	DWORD GetPixelColor(int _X, int _Y, DWORD _OutColor);

protected:

private:
	HDC				ImageDC = nullptr;
	HBITMAP		BitMap = nullptr;
	HBITMAP		OldBitMap = nullptr;
	BITMAP		Info = BITMAP();
	bool				IsCut = false;

	//Ŀ���� �̹��� �������� ����
	std::vector<ImageCutData> ImageCutDatas;

	//���� BITMAP�� ������ Info�� ����ϴ� �Լ� 
	void ImageScaleCheck();
};

