#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineLevel.h"
#include "GameEngineResources.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>


//GameEngineCore를 상속받는 객체는 싱글톤으로 제작됨
//때문에 유일하게 GameEngineCore를  상속받은 객체를 가르킴
GameEngineCore* Core;


//이 클래스를 상속받은 Core객체를 리턴
GameEngineCore* GameEngineCore::GetInst()
{
	return Core;
}



void GameEngineCore::GlobalStart()
{
	//GameEngineCore를 상속받은 자식의 Start가 실행됨
	Core->Start();

	//시간 측정 시작
	GameEngineTime::GlobalTime.Reset();
}

void GameEngineCore::GlobalUpdate()
{
	//씬 변경을 요구했다면
	if (nullptr != Core->NextLevel)
	{
		GameEngineLevel* PrevLevel = Core->MainLevel;
		GameEngineLevel* NextLevel = Core->NextLevel;

		if (nullptr != PrevLevel)
		{
			//기존 레벨이 끝났을때 처리할 작업 실행
			PrevLevel->LevelChangeEnd(NextLevel);
		}

		//현재 레벨 변경
		Core->MainLevel = NextLevel;
		Core->NextLevel = nullptr;

		if (nullptr != NextLevel)
		{
			//변경된 레벨이 시작될 때 처리할 작업 실행
			NextLevel->LevelChangeStart(PrevLevel);
		}
	}

	//이전 프레임과 현재 프레임 사이 시간
	float TimeDeltaTime = GameEngineTime::GlobalTime.TimeCheck();

	//키 입력 처리
	GameEngineInput::Update(TimeDeltaTime);

	//GameEngineCore를 상속받은 자식의 Update가 실행됨
	//코어에 대한 업데이트(...)
	Core->Update();

	//Core->Start에서 레벨을 지정해주어야 함
	if (nullptr == Core->MainLevel)
	{
		MsgAssert("레벨을 지정해주지 않은 상태로 코어를 실행했습니다");
		return;
	}

	//레벨의 업데이트 실행 
	Core->MainLevel->Update(TimeDeltaTime);

	//레벨에 존재하는 엑터들의 업데이트
	Core->MainLevel->ActorsUpdate(TimeDeltaTime);

	//더블 버퍼링 용 이미지 지우기
	GameEngineWindow::DoubleBufferClear();

	//더블버퍼 이미지에 엑터 렌더링
	Core->MainLevel->ActorsRender(TimeDeltaTime);

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



GameEngineCore::GameEngineCore()
{
	GameEngineDebug::LeakCheck();

	//GameEngineCore는 추상 클래스
	//때문에 이 this는 GameEngineCore를 상속받은 자식 객체가 된다
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



//이 프로그램의 첫 도입부
void GameEngineCore::CoreStart(HINSTANCE _instance)
{
	//윈도우 생성
	//GameEngineWindow::WindowCreate(_instance, "MainWindow", { 320 * 3, 224 * 3 }, { 0, 0 });
	GameEngineWindow::WindowCreate(_instance, "MainWindow", { 320.f * 3.f, 240.f * 3.f }, { 0, 0 });

	//이 안에서 무한 루프로 게임이 진행(콜백방식)
	GameEngineWindow::WindowLoop(GameEngineCore::GlobalStart, GameEngineCore::GlobalUpdate, GameEngineCore::GlobalEnd);
}


//레벨 변경
void GameEngineCore::ChangeLevel(const std::string_view& _Name)
{
	std::map<std::string, GameEngineLevel*>::iterator FindIter = Levels.find(_Name.data());

	if (FindIter == Levels.end())
	{
		std::string Name = _Name.data();
		MsgAssert(Name + "존재하지 않는 레벨을 실행시키려고 했습니다");
		return;
	}

	NextLevel = FindIter->second;
}


//레벨의 로딩함수(순수가상함수) 실행
void GameEngineCore::LevelLoading(GameEngineLevel* _Level)
{
	if (nullptr == _Level)
	{
		MsgAssert("nullptr 인 레벨을 로딩하려고 했습니다.");
		return;
	}

	_Level->Loading();
}