#pragma once
#include <Windows.h>

class GameEngineTime
{
public:
	GameEngineTime();
	~GameEngineTime();

	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(const GameEngineTime&& _Other) noexcept = delete;

	void TimeCheckStart();

	float TimeCheckEnd();

protected:

private:
	LARGE_INTEGER Prev			= LARGE_INTEGER();
	LARGE_INTEGER Current	= LARGE_INTEGER();
	LARGE_INTEGER Second		= LARGE_INTEGER();
};

