#pragma once
#include <Windows.h>
#include <map>
#include <string_view>
#include <GameEngineBase/GameEngineDebug.h>


class GameEngineLevel;

class GameEngineCore
{
private:
	static void GlobalStart();
	static void GlobalUpdate();
	static void GlobalEnd();

public:
	GameEngineCore();
	~GameEngineCore();

	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;

	//�� ���α׷��� ù ���Ժ�
	void CoreStart(HINSTANCE _instance);

	//���� ����
	void ChangeLevel(const std::string_view& _Name);

	//�� Ŭ������ ��ӹ��� Core��ü�� ����
	static GameEngineCore* GetInst();

protected:
	//������ ����
	template<typename LevelType>
	void CreateLevel(const std::string_view& _Name)
	{
		if (Levels.end() != Levels.find(_Name.data()))
		{
			std::string Name = _Name.data();
			MsgAssert(Name + "�̹� �����ϴ� �̸��� ������ ������� �߽��ϴ�");
			return;
		}

		GameEngineLevel* Level = new LevelType();
		LevelLoading(Level);
		Levels.insert(std::make_pair(_Name.data(), Level));
	}


	void DebugSwitch()
	{
		IsDebugValue = !IsDebugValue;
	}

	bool IsDebug()
	{
		return IsDebugValue;
	}


	//Global~�迭 �Լ����� �����
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void End() = 0;

private:
	bool																IsDebugValue	= false;
	std::map<std::string, GameEngineLevel*>	Levels;
	GameEngineLevel*										MainLevel		= nullptr;
	GameEngineLevel*										NextLevel		= nullptr;


	//������ �ε��Լ�(���������Լ�) ����
	void LevelLoading(GameEngineLevel* _Level);
};

