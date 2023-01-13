#include "GameEngineTime.h"

GameEngineTime GameEngineTime::GlobalTime;

GameEngineTime::GameEngineTime()
{
	//1�� ���� �߻��� Ŭ����
	QueryPerformanceFrequency(&Second);

	//���� �ð�(���ؽ÷κ��� ������� �߻��� Ŭ�� ��)
	QueryPerformanceCounter(&Prev);
}

GameEngineTime::~GameEngineTime()
{
}

void GameEngineTime::Reset()
{
	QueryPerformanceCounter(&Prev);
}

float GameEngineTime::TimeCheck()
{
	QueryPerformanceCounter(&Current);

	//�ð��� �����ϱ� ������ ���ķ� ����� Ŭ���� �߻��ߴ°�
	Tick = Current.QuadPart - Prev.QuadPart;

	//(����ð� - �����ð�) / 1�ʴ� �߻��ϴ� Ŭ����
	DoubleDeltaTime = (static_cast<double>(Current.QuadPart) - static_cast<double>(Prev.QuadPart)) / static_cast<double>(Second.QuadPart);

	//�����ð� ����ð����� �簻��
	Prev.QuadPart = Current.QuadPart;

	floatDeltaTime = static_cast<float>(DoubleDeltaTime);
	return floatDeltaTime;
}
