#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineLevel.h"
#include "GameEngineResources.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>


//GameEngineCore�� ��ӹ޴� ��ü�� �̱������� ���۵�
//������ �����ϰ� GameEngineCore��  ��ӹ��� ��ü�� ����Ŵ
GameEngineCore* Core;


//�� Ŭ������ ��ӹ��� Core��ü�� ����
GameEngineCore* GameEngineCore::GetInst()
{
	return Core;
}



void GameEngineCore::GlobalStart()
{
	//GameEngineCore�� ��ӹ��� �ڽ��� Start�� �����
	Core->Start();

	//�ð� ���� ����
	GameEngineTime::GlobalTime.Reset();
}

void GameEngineCore::GlobalUpdate()
{
	//�� ������ �䱸�ߴٸ�
	if (nullptr != Core->NextLevel)
	{
		GameEngineLevel* PrevLevel = Core->MainLevel;
		GameEngineLevel* NextLevel = Core->NextLevel;

		if (nullptr != PrevLevel)
		{
			//���� ������ �������� ó���� �۾� ����
			PrevLevel->LevelChangeEnd(NextLevel);
		}

		//���� ���� ����
		Core->MainLevel = NextLevel;
		Core->NextLevel = nullptr;

		if (nullptr != NextLevel)
		{
			//����� ������ ���۵� �� ó���� �۾� ����
			NextLevel->LevelChangeStart(PrevLevel);
		}
	}

	//���� �����Ӱ� ���� ������ ���� �ð�
	float TimeDeltaTime = GameEngineTime::GlobalTime.TimeCheck();

	//Ű �Է� ó��
	GameEngineInput::Update(TimeDeltaTime);

	//GameEngineCore�� ��ӹ��� �ڽ��� Update�� �����
	//�ھ ���� ������Ʈ(...)
	Core->Update();

	//Core->Start���� ������ �������־�� ��
	if (nullptr == Core->MainLevel)
	{
		MsgAssert("������ ���������� ���� ���·� �ھ �����߽��ϴ�");
		return;
	}

	//������ ������Ʈ ���� 
	Core->MainLevel->Update(TimeDeltaTime);

	//������ �����ϴ� ���͵��� ������Ʈ
	Core->MainLevel->ActorsUpdate(TimeDeltaTime);

	//���� ���۸� �� �̹��� �����
	GameEngineWindow::DoubleBufferClear();

	//������� �̹����� ���� ������
	Core->MainLevel->ActorsRender(TimeDeltaTime);

	//���� ���� -> ������ �����
	GameEngineWindow::DoubleBufferRender();
}

void GameEngineCore::GlobalEnd()
{
	//GameEngineCore�� ��ӹ��� �ڽ��� End�� �����
	Core->End();

	//������ Level::Loading���� �ε��� ���ҽ����� ������
	GameEngineResources::GetInst().Release();
}



GameEngineCore::GameEngineCore()
{
	GameEngineDebug::LeakCheck();

	//GameEngineCore�� �߻� Ŭ����
	//������ �� this�� GameEngineCore�� ��ӹ��� �ڽ� ��ü�� �ȴ�
	Core = this;
}

GameEngineCore::~GameEngineCore()
{
	std::map<std::string, GameEngineLevel*>::iterator StartIter = Levels.begin();
	std::map<std::string, GameEngineLevel*>::iterator EndIter = Levels.end();

	for (size_t i = 0; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
		}
	}

	Levels.clear();
}



//�� ���α׷��� ù ���Ժ�
void GameEngineCore::CoreStart(HINSTANCE _instance)
{
	//������ ����
	//GameEngineWindow::WindowCreate(_instance, "MainWindow", { 320 * 3, 224 * 3 }, { 0, 0 });
	GameEngineWindow::WindowCreate(_instance, "MainWindow", { 320.f * 3.f, 240.f * 3.f }, { 0, 0 });

	//�� �ȿ��� ���� ������ ������ ����(�ݹ���)
	GameEngineWindow::WindowLoop(GameEngineCore::GlobalStart, GameEngineCore::GlobalUpdate, GameEngineCore::GlobalEnd);
}


//���� ����
void GameEngineCore::ChangeLevel(const std::string_view& _Name)
{
	std::map<std::string, GameEngineLevel*>::iterator FindIter = Levels.find(_Name.data());

	if (FindIter == Levels.end())
	{
		std::string Name = _Name.data();
		MsgAssert(Name + "�������� �ʴ� ������ �����Ű���� �߽��ϴ�");
		return;
	}

	NextLevel = FindIter->second;
}


//������ �ε��Լ�(���������Լ�) ����
void GameEngineCore::LevelLoading(GameEngineLevel* _Level)
{
	if (nullptr == _Level)
	{
		MsgAssert("nullptr �� ������ �ε��Ϸ��� �߽��ϴ�.");
		return;
	}

	_Level->Loading();
}