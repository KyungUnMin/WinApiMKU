#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineLevel::GameEngineLevel()
{
}

GameEngineLevel::~GameEngineLevel()
{
	//������ ���� ����
	for (std::pair<int, std::list<GameEngineActor*>> UpdateGroup : Actors)
	{
		std::list<GameEngineActor*>& ActorList = UpdateGroup.second;

		for (GameEngineActor* Actor : ActorList)
		{
			if (nullptr != Actor)
			{
				delete Actor;
				Actor = nullptr;
			}
		}
	}

	Actors.clear();
}


//���Ͱ� ������ �� ȣ��(CreateActor), ������ Startȣ��
void GameEngineLevel::ActorStart(GameEngineActor* _Actor, int _Order)
{
	if (nullptr == _Actor)
	{
		MsgAssert("nullptr ���͸� Start�Ϸ��� �߽��ϴ�.");
		return;
	}

	_Actor->SetOrder(_Order);
	_Actor->Start();
}


//�� ������ �����ϴ� ��� ���͵��� Order������ Updateȣ��
void GameEngineLevel::ActorsUpdate()
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

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
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

		for (GameEngineActor* Actor : ActorList)
		{
			if (nullptr == Actor)
				continue;

			Actor->Render();
		}
	}

}