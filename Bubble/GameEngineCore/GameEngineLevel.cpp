#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineLevel::GameEngineLevel() 
{
}

GameEngineLevel::~GameEngineLevel() 
{
	//생성한 엑터 삭제
	for (std::pair<int,std::list<GameEngineActor*>> UpdateGroup : Actors)
	{
		std::list<GameEngineActor*>& ActorList = UpdateGroup.second;

		for (GameEngineActor* Actor : ActorList)
		{
			if (nullptr == Actor)
				continue;

			delete Actor;
			Actor = nullptr;
		}
	}

	Actors.clear();
}

//엑터가 생성될 때 호출(CreateActor), 엑터의 Start호출
void GameEngineLevel::ActorStart(GameEngineActor* _Actor)
{
	if (nullptr == _Actor)
	{
		MsgAssert("nullptr Actor를 사용 시도");
		return;
	}

	_Actor->Start();
}

//이 레벨에 존재하는 모든 엑터들을 Order순으로 Update호출
void GameEngineLevel::ActorsUpdate()
{
	for (auto Iter = Actors.begin(); Iter != Actors.end(); ++Iter)
	{
		std::list<GameEngineActor*>& ActorList = Iter->second;
		for (GameEngineActor* Actor : ActorList)
		{
			if (nullptr == Actor)
				continue;

			Actor->Update();
		}
	}

}

//이 레벨에 존재하는 모든 엑터들을 Order순으로 Render
void GameEngineLevel::ActorsRender()
{
	for (auto Iter = Actors.begin(); Iter != Actors.end(); ++Iter)
	{
		std::list<GameEngineActor*>& ActorList = Iter->second;
		for (GameEngineActor* Actor : ActorList)
		{
			if (nullptr == Actor)
				continue;

			Actor->Render();
		}
	}

}


