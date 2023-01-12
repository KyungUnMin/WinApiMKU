#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <Windows.h>

class GameEngineLevel;
class GameEngineActor
{
	friend GameEngineLevel;

public:
	GameEngineActor();
	~GameEngineActor();

	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	float4 GetPos()
	{
		return Pos;
	}

	void SetPos(const float4& _MovePos)
	{
		Pos = _MovePos;
	}

	void SetMove(const float4& _MovePos)
	{
		Pos += _MovePos;
	}

protected:
	virtual void Start() {}
	virtual void Update() {}
	virtual void Render() {}

private:
	int		Order;
	float4	Pos		= { 0.0f, 0.0f };

	void SetOrder(int _Order)
	{
		Order = _Order;
	}
};

