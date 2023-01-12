#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineLevel::GameEngineLevel() 
{
}

GameEngineLevel::~GameEngineLevel() 
{
	//������ ���� ����
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

//���Ͱ� ������ �� ȣ��(CreateActor), ������ Startȣ��
void GameEngineLevel::ActorStart(GameEngineActor* _Actor)
{
	if (nullptr == _Actor)
	{
		MsgAssert("nullptr Actor�� ��� �õ�");
		return;
	}

	_Actor->Start();
}

//�� ������ �����ϴ� ��� ���͵��� Order������ Updateȣ��
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

//�� ������ �����ϴ� ��� ���͵��� Order������ Render
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


