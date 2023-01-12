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

	//이 프로그램의 첫 도입부
	void CoreStart(HINSTANCE _instance);

protected:
	//레벨을 생성
	template<typename LevelType>
	void CreateLevel(const std::string_view& _Name)
	{
		if (Levels.end() != Levels.find(_Name.data()))
		{
			std::string Name = _Name.data();
			MsgAssert(Name + "이미 존재하는 이름의 레벨을 만들려고 했습니다");
			return;
		}

		GameEngineLevel* Level = new LevelType();
		LevelLoading(Level);
		Levels.insert(std::make_pair(_Name.data(), Level));
	}

	//레벨 변경
	void ChangeLevel(const std::string_view& _Name);

	//Global~계열 함수에서 실행됨
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void End() = 0;

private:
	std::map<std::string, GameEngineLevel*>	Levels;
	GameEngineLevel*										MainLevel = nullptr;

	//레벨의 로딩함수(순수가상함수) 실행
	void LevelLoading(GameEngineLevel* _Level);
};

