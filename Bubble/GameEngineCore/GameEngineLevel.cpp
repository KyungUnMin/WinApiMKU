#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineRender.h"

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

	_Actor->Level = this;
	_Actor->SetOrder(_Order);
	_Actor->Start();
}


//�� ������ �����ϴ� ��� ���͵��� Order������ Updateȣ��
void GameEngineLevel::ActorsUpdate(float _DeltaTime)
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

		for (GameEngineActor* Actor : ActorList)
		{
			if (nullptr == Actor || false == Actor->IsUpdate())
			{
				continue;
			}

			Actor->LiveTime += _DeltaTime;
			Actor->Update(_DeltaTime);
		}
	}

}


//�� ������ �����ϴ� ��� ���͵��� Order������ Render
void GameEngineLevel::ActorsRender(float _DeltaTime)
{
	//GameEngineRender�� Render�� ȣ��
	{
		std::map<int, std::list<GameEngineRender*>>::iterator GroupStartIter = Renders.begin();
		std::map<int, std::list<GameEngineRender*>>::iterator GroupEndIter = Renders.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineRender*>& ActorList = GroupStartIter->second;

			for (GameEngineRender* Render : ActorList)
			{
				if (nullptr == Render || false == Render->IsUpdate())
					continue;

				Render->Render(_DeltaTime);
			}
		}
	}


	//Actor::Render�� ȣ��
	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

			for (GameEngineActor* Actor : ActorList)
			{
				if (nullptr == Actor || false == Actor->IsUpdate())
					continue;

				Actor->Render(_DeltaTime);
			}
		}
	}


}


//Renders�� GameEngineRender�� ���(GameEngineRender::SetOrder���� ���� ȣ��)
void GameEngineLevel::PushRender(GameEngineRender* _Render)
{
	if(nullptr == _Render)
	{
		MsgAssert("nullptr�� GameEngineRender�� ������ �׷� �ӿ� �������� �߽��ϴ�");
		return;
	}

	Renders[_Render->GetOrder()].push_back(_Render);
}