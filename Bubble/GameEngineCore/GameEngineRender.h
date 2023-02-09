#pragma once
#include <map>
#include <string.h>
#include <string_view>
#include <GameEnginePlatform/GameEngineImage.h>
#include "GameEngineComponent.h"

//CreateAnimation �Լ��� ���ڰ� �� ����ü
class FrameAnimationParameter
{
public:
	//Ű������ ����� �ִϸ��̼� �̸�
	std::string_view		AnimationName	= "";

	//�ҷ��� �̹��� �̸�
	std::string_view		ImageName			= "";


	//�ִϸ��̼� �������� �������� ��� 
	//���� �������ε����� �� ������ �ε����� ����
	int							Start					= 0;
	int							End						= 0;

	//������ �ε���
	//int						CurrentIndex		= 0;

	//�ִϸ��̼� �����Ӹ��� ��� �ð��� ���� ��� ��� �������� ��� �ð� ����
	float						InterTimer			= 0.1f;

	bool							Loop					= true;

	//�ִϸ��̼� �������� ���������� ��µ��� �ʴ� ��� ���⼭ ���� �������ش�
	std::vector<int>		FrameIndex;
	//�ִϸ��̼� �����Ӹ��� ��� �ð��� �ٸ� ��� ���⼭ ���� �������ش�
	std::vector<float>	FrameTime;
};

class GameEngineActor;
class GameEngineLevel;

//����(Owner)�� �������� �̹���/�ִϸ��̼��� ������ ���ִ� ��ü, Level���� ������
class GameEngineRender : public GameEngineComponent
{
	friend GameEngineActor;
	friend GameEngineLevel;

public:
	GameEngineRender();
	~GameEngineRender();

	GameEngineRender(const GameEngineRender& _Other) = delete;
	GameEngineRender(GameEngineRender&& _Other) noexcept = delete;
	GameEngineRender& operator=(const GameEngineRender& _Other) = delete;
	GameEngineRender& operator=(const GameEngineRender&& _Other) noexcept = delete;

	//GameEngineResources���� �̹��� ã�ƿ���
	void SetImage(const std::string_view& _ImageName);

	//�̹��� �����ϰ� ũ�⵵ ���ҽ��� �̹���ũ��� ����
	void SetImageToScaleToImage(const std::string_view& _ImageName);

	//������ �̹����� ���� ���ҽ��� �̹��� ũ��� ����
	void SetScaleToImage();


	//������ ���� ����
	void SetFrame(int _Frame);


	inline GameEngineImage* GetImage()
	{
		return Image;
	}

	inline int GetFrame()
	{
		return Frame;
	}


	//TransparentBlt�Ҷ� ���� ������ ����
	inline void SetTransColor(int _Color)
	{
		TransColor = _Color;
	}

	//ī�޶� ���� �޴��� ���� ����
	inline void SetEffectCamera(bool _Effect)
	{
		IsEffectCamera = _Effect;
	}

	
	//ī�޶� ���� ����
	inline void EffectCameraOff()
	{
		SetEffectCamera(false);
	}

	//ī�޶� ���� �ѱ�
	inline void EffectCameraOn()
	{
		SetEffectCamera(true);
	}


	bool IsAnimationEnd();
	
	//�ִϸ��̼� ����
	void CreateAnimation(const FrameAnimationParameter& _Parameter);

	//�ִϸ��̼� ��ȯ
	void ChangeAnimation(const std::string_view& _AnimationName, bool _ForceChange = false);


	//(Actor�� CreateRender���� ȣ��)
	//������ �Ǵ� ���� ���� �� Level�� Renders�� ���
	void SetOrder(int _Order) override;

	//�� �Լ��� ���� ���� �����ϸ� TextRender��尡 �ȴ�
	void SetText(const std::string_view& _Text);

protected:

private:
	//�̹��� ���ҽ��� ����� GameEngineImage
	GameEngineImage*		Image					= nullptr;

	//�̹����� �߶����� �׸� �̹��� �ε���
	int								Frame					= 0;

	//Render�Լ����� TransparentBlt�Ҷ� ���� ������
	int								TransColor			= RGB(147, 187, 236);

	//������ �� �� ī�޶� ������ �޴��� ����
	bool								IsEffectCamera	= true;


	//�� ���� ������ �����ϸ� TextRender�� ����
	std::string RenderText;

	//Level�� Render�� ���� ���� �������Ǵ� �Լ�
	void Render(float _DeltaTime);

	//������ ������ �ؽ�Ʈ ������
	void TextRender(float _DeltaTime);
	//������ ������ �̹��� ������
	void ImageRender(float _DeltaTime);


	//�ִϸ��̼ǿ� ���� ������ �ۿ����� �ʿ����� �ʴ�. ������ private
	//������ �̹����� ���� �ִϸ��̼� ����(�� �߷��ִ� �̹������� ��)
	class FrameAnimation
	{
	public:
		//�� �ִϸ��̼��� ���� ����
		GameEngineRender*	Parent					= nullptr;
		GameEngineImage*		Image					= nullptr;

		//�ִϸ��̼��� �׸� �߸� �̹��� �ε���
		std::vector<int>			FrameIndex;
		//�ش� �����Ӹ��� �ӹ��� �ð�
		std::vector<float>		FrameTime;

		//���� ��µǰ� �ִ� ������ �ε���
		int								CurrentIndex		= 0;
		//���� �������� ���� ���������� �Ѿ����� �����ִ� �ð�
		float							CurrentTime		= 0.0f;
		//�ݺ� ����
		bool								Loop					= true;

		bool IsEnd();

		//CurrentTime���� FrameIndex[CurrentIndex]�� �������� �������� �ε��� ����
		void Render(float _DeltaTime);

		void Reset()
		{
			CurrentIndex = 0;
			CurrentTime = 0.0f;
		}
	};

	std::map<std::string, FrameAnimation>	Animation;
	FrameAnimation*									CurrentAnimation = nullptr;
};

