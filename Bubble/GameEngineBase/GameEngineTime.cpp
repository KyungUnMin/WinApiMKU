#include "GameEngineTime.h"

GameEngineTime::GameEngineTime()
{
	//1�� ���� �߻��� Ŭ����
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
