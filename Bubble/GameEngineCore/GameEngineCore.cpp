#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineLevel.h"
#include "GameEngineResources.h"

//GameEngineCore를 상속받는 객체는 싱글톤으로 제작됨
//때문에 유일하게 GameEngineCore를  상속받은 객체를 가르킴
GameEngineCore* Core;

GameEngineCore::GameEngineCore()
{
	GameEngineDebug::LeakCheck();

	//GameEngineCore는 추상 클래스
	//때문에 이 this는 GameEngineCore를 상속받은 자식 객체가 된다
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

//이 프로그램의 첫 도입부
void GameEngineCore::CoreStart(HINSTANCE _instance)
{
	//윈도우 생성
	GameEngineWindow::WindowCreate(_instance, "BubbleBubble2", { 960, 672 }, { 0, 0 });

	//이 안에서 무한 루프로 게임이 진행(콜백방식)
	GameEngineWindow::WindowLoop(GameEngineCore::GlobalStart, GameEngineCore::GlobalUpdate, GameEngineCore::GlobalEnd);
}

void GameEngineCore::GlobalStart()
{
	//GameEngineCore를 상속받은 자식의 Start가 실행됨
	Core->Start();
}

void GameEngineCore::GlobalUpdate()
{
	//GameEngineCore를 상속받은 자식의 Update가 실행됨
	//코어에 대한 업데이트(...)
	Core->Update();

	//Core->Start에서 레벨을 지정해주어야 함
	if (nullptr == Core->MainLevel)
	{
		MsgAssert("레벨을 지정해 주지 않음");
		return;
	}

	//레벨에 존재하는 엑터들의 업데이트
	Core->MainLevel->ActorsUpdate();

	//더블 버퍼링 용 이미지 지우기
	GameEngineWindow::DoubleBufferClear();

	//더블버퍼 이미지에 엑터 렌더링
	Core->MainLevel->ActorsRender();

	//더블 버퍼 -> 윈도우 백버퍼
	GameEngineWindow::DoubleBufferRender();
}

void GameEngineCore::GlobalEnd()
{
	//GameEngineCore를 상속받은 자식의 End가 실행됨
	Core->End();

	//각각의 Level::Loading에서 로드한 리소스들을 삭제함
	GameEngineResources::GetInst().Release();
}

void GameEngineCore::LevelLoading(GameEngineLevel* _Level)
{
	if (nullptr == _Level)
	{
		MsgAssert("nullptr인 레벨 로딩 시도");
		return;
	}

	_Level->Loading();
}

void GameEngineCore::ChangeLevel(const std::string_view& _Name)
{
	auto iter = Levels.find(_Name.data());

	//존재하지 않는(등록하지 않은) 레벨의 이름인 경우
	if (iter == Levels.end())
	{
		std::string Name = _Name.data();
		MsgAssert(Name + " : 존재하지 않는 레벨로 변환하려고 시도함");
		return;
	}

	MainLevel = iter->second;
}