#pragma once
#include <GameEnginePlatform/GameEngineImage.h>

class GameEngineActor;
class GameEngineLevel;

//����(Owner)�� �������� �̹���/�ִϸ��̼��� ������ ���ִ� ��ü, Level���� ������
class GameEngineRender
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

	//Rendering�Ǵ� ����
	inline int GetOrder()
	{
		return Order;
	}

protected:

private:
	//�� ��ü�� ������ �ִ� ����Actor
	GameEngineActor*		Owner			= nullptr;

	//������ �Ǵ� ����
	int								Order			= 0;

	//Owner ���� �����ġ(������)
	float4							Position		= float4::Zero;

	//�̹����� �׸� ũ��
	float4							Scale			= float4::Zero;

	//�̹��� ���ҽ��� ����� GameEngineImage
	GameEngineImage*		Image			= nullptr;

	//�̹����� �߶����� �׸� �̹��� �ε���
	int								Frame			= 0;



	//������ �Ǵ� ���� ���� �� Level�� Renders�� ���(Actor������ ȣ��)
	void SetOrder(int _Order);

	//Level�� Render�� ���� ���� �������Ǵ� �Լ�
	void Render(float _DeltaTime);
};

