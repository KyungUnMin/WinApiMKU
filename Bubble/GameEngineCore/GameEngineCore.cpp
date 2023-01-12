#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineLevel.h"
#include "GameEngineResources.h"

//GameEngineCore�� ��ӹ޴� ��ü�� �̱������� ���۵�
//������ �����ϰ� GameEngineCore��  ��ӹ��� ��ü�� ����Ŵ
GameEngineCore* Core;

GameEngineCore::GameEngineCore()
{
	GameEngineDebug::LeakCheck();

	//GameEngineCore�� �߻� Ŭ����
	//������ �� this�� GameEngineCore�� ��ӹ��� �ڽ� ��ü�� �ȴ�
	Core = this;
}

GameEngineCore::~GameEngineCore()
{
	for (auto iter = Levels.begin(); iter != Levels.end(); ++iter)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}

	Levels.clear();
}

//�� ���α׷��� ù ���Ժ�
void GameEngineCore::CoreStart(HINSTANCE _instance)
{
	//������ ����
	GameEngineWindow::WindowCreate(_instance, "BubbleBubble2", { 960, 672 }, { 0, 0 });

	//�� �ȿ��� ���� ������ ������ ����(�ݹ���)
	GameEngineWindow::WindowLoop(GameEngineCore::GlobalStart, GameEngineCore::GlobalUpdate, GameEngineCore::GlobalEnd);
}

void GameEngineCore::GlobalStart()
{
	//GameEngineCore�� ��ӹ��� �ڽ��� Start�� �����
	Core->Start();
}

void GameEngineCore::GlobalUpdate()
{
	//GameEngineCore�� ��ӹ��� �ڽ��� Update�� �����
	//�ھ ���� ������Ʈ(...)
	Core->Update();

	//Core->Start���� ������ �������־�� ��
	if (nullptr == Core->MainLevel)
	{
		MsgAssert("������ ������ ���� ����");
		return;
	}

	//������ �����ϴ� ���͵��� ������Ʈ
	Core->MainLevel->ActorsUpdate();

	//���� ���۸� �� �̹��� �����
	GameEngineWindow::DoubleBufferClear();

	//������� �̹����� ���� ������
	Core->MainLevel->ActorsRender();

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

void GameEngineCore::LevelLoading(GameEngineLevel* _Level)
{
	if (nullptr == _Level)
	{
		MsgAssert("nullptr�� ���� �ε� �õ�");
		return;
	}

	_Level->Loading();
}

void GameEngineCore::ChangeLevel(const std::string_view& _Name)
{
	auto iter = Levels.find(_Name.data());

	//�������� �ʴ�(������� ����) ������ �̸��� ���
	if (iter == Levels.end())
	{
		std::string Name = _Name.data();
		MsgAssert(Name + " : �������� �ʴ� ������ ��ȯ�Ϸ��� �õ���");
		return;
	}

	MainLevel = iter->second;
}