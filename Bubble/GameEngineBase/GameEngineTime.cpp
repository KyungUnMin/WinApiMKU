#include "GameEngineTime.h"

GameEngineTime::GameEngineTime() 
{
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