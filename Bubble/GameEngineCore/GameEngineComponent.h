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

	
	//Offset 적용
	inline void SetPosition(const float4& _Position)
	{
		Position = _Position;
	}

	//이미지의 상대위치값을 _Position만큼 움직인다
	inline void SetMove(float4 _Position)
	{
		Position += _Position;
	}

	//크기 설정
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

	//이 렌더를 소유하고 있는 엑터 반환
	GameEngineActor* GetActor();

	//Actor의 Pos + Position(상대위치)
	float4 GetActorPlusPos();

protected:

private:
	//Actor에 따른 Offset(상대위치)
	float4		Position = float4::Zero;
	float4		Scale = float4::Zero;
};

