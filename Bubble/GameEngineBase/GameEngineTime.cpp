#include "GameEngineTime.h"

GameEngineTime::GameEngineTime()
{
	//1초 동안 발생한 클럭수
	QueryPerformanceFrequency(&Second);
}

GameEngineTime::~GameEngineTime()
{

}

void GameEngineTime::TimeCheckStart()
{
	QueryPerformanceCounter(&Prev);
}

float GameEngineTime::TimeCheckEnd()
{

	return 0.0f;
}
