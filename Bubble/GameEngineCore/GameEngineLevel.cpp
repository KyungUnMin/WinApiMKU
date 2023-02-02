#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineRender.h"
#include "GameEngineCollision.h"

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

	_Actor->SetOwner(this);
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



void GameEngineLevel::Release()
{
	//�ݸ��� ����
	{
		std::map<int, std::list<GameEngineCollision*>>::iterator GroupStartIter = Collisions.begin();
		std::map<int, std::list<GameEngineCollision*>>::iterator GroupEndIter = Collisions.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineCollision*>& CollisionList = GroupStartIter->second;

			std::list<GameEngineCollision*>::iterator CollisionStartIter = CollisionList.begin();
			std::list<GameEngineCollision*>::iterator CollisionEndIter = CollisionList.end();

			for (; CollisionStartIter != CollisionEndIter;)
			{
				GameEngineCollision* ReleaseCollision = *CollisionStartIter;

				if (nullptr != ReleaseCollision && false == ReleaseCollision->IsDeath())
				{
					++CollisionStartIter;
					continue;
				}

				CollisionStartIter = CollisionList.erase(CollisionStartIter);
			}
		}
	}


	//������ ����
	{
		std::map<int, std::list<GameEngineRender*>>::iterator GroupStartIter = Renders.begin();
		std::map<int, std::list<GameEngineRender*>>::iterator GroupEndIter = Renders.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineRender*>& RenderList = GroupStartIter->second;

			std::list<GameEngineRender*>::iterator RenderStartIter = RenderList.begin();
			std::list<GameEngineRender*>::iterator RenderEndIter = RenderList.end();

			for (; RenderStartIter != RenderEndIter;)
			{
				GameEngineRender* ReleaseRender = *RenderStartIter;

				if (nullptr != ReleaseRender && false == ReleaseRender->IsDeath())
				{
					++RenderStartIter;
					continue;
				}

				RenderStartIter = RenderList.erase(RenderStartIter);
			}
		}
	}

	//���� ����(���� ���� Render�� Collision�� ����)
	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

			std::list<GameEngineActor*>::iterator ActorStartIter = ActorList.begin();
			std::list<GameEngineActor*>::iterator ActorEndIter = ActorList.end();

			for (; ActorStartIter != ActorEndIter;)
			{
				GameEngineActor* ReleaseActor = *ActorStartIter;

				if (nullptr != ReleaseActor && false == ReleaseActor->IsDeath())
				{
					++ActorStartIter;
					continue;
				}

				ActorStartIter = ActorList.erase(ActorStartIter);
				delete ReleaseActor;
				ReleaseActor = nullptr;
			}
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

void GameEngineLevel::PushCollision(GameEngineCollision* _Collision)
{
	if (nullptr == _Collision)
	{
		MsgAssert("nullptr�� �浹ü�� �浹 �׷�ӿ� �������� �߽��ϴ�.");
	}

	Collisions[_Collision->GetOrder()].push_back(_Collision);
}
