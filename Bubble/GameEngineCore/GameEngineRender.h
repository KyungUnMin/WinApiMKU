#pragma once
#include <map>
#include <string.h>
#include <string_view>
#include <GameEnginePlatform/GameEngineImage.h>
#include "GameEngineObject.h"

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
class GameEngineRender : public GameEngineObject
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


	//Offset ����
	inline void SetPosition(const float4& _Position)
	{
		Position = _Position;
	}

	//ũ�� ����
	inline void SetScale(const float4& _Scale)
	{
		Scale = _Scale;
	}

	//�̹����� �����ġ���� _Position��ŭ �����δ�
	inline void SetMove(float4 _Position)
	{
		Position += _Position;
	}

	//������ �̹����� ���� ���ҽ��� �̹��� ũ��� ����
	void SetScaleToImage();

	//������ ���� ����
	void SetFrame(int _Frame);

	inline GameEngineImage* GetImage()
	{
		return Image;
	}

	//Rendering�Ǵ� ����
	inline int GetOrder()
	{
		return Order;
	}

	inline int GetFrame()
	{
		return Frame;
	}

	//�� ������ �����ϰ� �ִ� ���� ��ȯ
	GameEngineActor* GetActor();

	//TransparentBlt�Ҷ� ���� ������ ����
	inline void SetTransColor(int _Color)
	{
		TransColor = _Color;
	}

	inline float4 GetPosition()
	{
		return Position;
	}

	inline float4 GetScale()
	{
		return Scale;
	}

	//ī�޶� ���� ����
	inline void EffectCameraOff()
	{
		IsEffectCamera = false;
	}
	
	//�ִϸ��̼� ����
	void CreateAnimation(const FrameAnimationParameter& _Parameter);

	//�ִϸ��̼� ��ȯ
	void ChangeAnimation(const std::string_view& _AnimationName, bool _ForceChange = false);

protected:

private:
	//������ �Ǵ� ����
	int								Order					= 0;

	//Owner ���� �����ġ(������)
	float4							Position				= float4::Zero;

	//�̹����� �׸� ũ��
	float4							Scale					= float4::Zero;

	//�̹��� ���ҽ��� ����� GameEngineImage
	GameEngineImage*		Image					= nullptr;

	//�̹����� �߶����� �׸� �̹��� �ε���
	int								Frame					= 0;

	//Render�Լ����� TransparentBlt�Ҷ� ���� ������
	int								TransColor			= RGB(147, 187, 236);

	//������ �� �� ī�޶� ������ �޴��� ����
	bool								IsEffectCamera	= true;


	//������ �Ǵ� ���� ���� �� Level�� Renders�� ���(Actor������ ȣ��)
	void SetOrder(int _Order);

	//Level�� Render�� ���� ���� �������Ǵ� �Լ�
	void Render(float _DeltaTime);


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

