#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"

class GameEngineActor;

class GameEngineComponent : public GameEngineObject
{
public:
	GameEngineComponent();
	~GameEngineComponent();

	GameEngineComponent(const GameEngineComponent& _Other) = delete;
	GameEngineComponent(GameEngineComponent&& _Other) noexcept = delete;
	GameEngineComponent& operator=(const GameEngineComponent& _Other) = delete;
	GameEngineComponent& operator=(const GameEngineComponent&& _Other) noexcept = delete;

	
	//Offset ����
	inline void SetPosition(const float4& _Position)
	{
		Position = _Position;
	}

	//�̹����� �����ġ���� _Position��ŭ �����δ�
	inline void SetMove(float4 _Position)
	{
		Position += _Position;
	}

	//ũ�� ����
	inline void SetScale(const float4& _Scale)
	{
		Scale = _Scale;
	}

	inline float4 GetPosition()
	{
		return Position;
	}

	inline float4 GetScale()
	{
		return Scale;
	}

	//�� ������ �����ϰ� �ִ� ���� ��ȯ
	GameEngineActor* GetActor();

	//Actor�� Pos + Position(�����ġ)
	float4 GetActorPlusPos();

protected:

private:
	//Actor�� ���� Offset(�����ġ)
	float4		Position = float4::Zero;
	float4		Scale = float4::Zero;
};

