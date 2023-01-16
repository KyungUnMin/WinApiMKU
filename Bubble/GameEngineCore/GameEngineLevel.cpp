#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineRender.h"

GameEngineLevel::GameEngineLevel()
{
}

GameEngineLevel::~GameEngineLevel()
{
	//생성한 엑터 삭제
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


//엑터가 생성될 때 호출(CreateActor), 엑터의 Start호출
void GameEngineLevel::ActorStart(GameEngineActor* _Actor, int _Order)
{
	if (nullptr == _Actor)
	{
		MsgAssert("nullptr 액터를 Start하려고 했습니다.");
		return;
	}

	_Actor->Level = this;
	_Actor->SetOrder(_Order);
	_Actor->Start();
}


//이 레벨에 존재하는 모든 엑터들을 Order순으로 Update호출
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


//이 레벨에 존재하는 모든 엑터들을 Order순으로 Render
void GameEngineLevel::ActorsRender(float _DeltaTime)
{
	//GameEngineRender의 Render를 호출
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


	//Actor::Render를 호출
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


//Renders에 GameEngineRender를 등록(GameEngineRender::SetOrder에서 직접 호출)
void GameEngineLevel::PushRender(GameEngineRender* _Render)
{
	if(nullptr == _Render)
	{
		MsgAssert("nullptr인 GameEngineRender를 렌더링 그룹 속에 넣으려고 했습니다");
		return;
	}

	Renders[_Render->GetOrder()].push_back(_Render);
}