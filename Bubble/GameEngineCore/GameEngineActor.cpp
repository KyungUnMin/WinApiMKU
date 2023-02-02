#include "GameEngineActor.h"
#include "GameEngineRender.h"
#include "GameEngineLevel.h"
#include "GameEngineCollision.h"

GameEngineActor::GameEngineActor()
{
}

GameEngineActor::~GameEngineActor()
{
	for (GameEngineRender* _Render : RenderList)
	{
		if (nullptr == _Render)
			continue;

		delete _Render;
		_Render = nullptr;
	}

	for (GameEngineCollision* _Collision : CollisionList)
	{
		if (nullptr == _Collision)
		{
			continue;
		}

		delete _Collision;
		_Collision = nullptr;
	}
}


GameEngineLevel* GameEngineActor::GetLevel()
{
	return GetOwner<GameEngineLevel>();
}

//CreateRender(int _Order)를 래핑 및 이미지 가져오기
GameEngineRender* GameEngineActor::CreateRender(const std::string_view& _Image, int _Order)
{
	GameEngineRender* Render = CreateRender(_Order);
	Render->SetImage(_Image);
	return Render;
}

//GameEngineRender를 생성 및 연결하고 Level의 RenderList에 등록
GameEngineRender* GameEngineActor::CreateRender(int _Order)
{
	GameEngineRender* Render = new GameEngineRender;
	Render->SetOwner(this);
	Render->SetOrder(_Order);
	RenderList.push_back(Render);
	return Render;
}

GameEngineCollision* GameEngineActor::CreateCollision(int _GroupIndex)
{
	GameEngineCollision* Collision = new GameEngineCollision;
	Collision->SetOwner(this);
	Collision->SetOrder(_GroupIndex);
	CollisionList.push_back(Collision);
	return Collision;
}

//Actor의 컴포넌트가 Death상태라면 Delete하기
void GameEngineActor::Release()
{
	//Death인 Render삭제
	{
		std::list<GameEngineRender*>::iterator StartIter = RenderList.begin();
		std::list<GameEngineRender*>::iterator EndIter = RenderList.end();

		for (; StartIter != EndIter; )
		{
			GameEngineRender* ReleaseRender = *StartIter;

			if (nullptr == ReleaseRender)
			{
				MsgAssert("nullptr 인 랜더가 내부에 들어있습니다.");
			}

			if (false == ReleaseRender->IsDeath())
			{
				++StartIter;
				continue;
			}

			StartIter = RenderList.erase(StartIter);

			delete ReleaseRender;
			ReleaseRender = nullptr;
		}
	}

	//Death인 Collision삭제
	{
		std::list<GameEngineCollision*>::iterator StartIter = CollisionList.begin();
		std::list<GameEngineCollision*>::iterator EndIter = CollisionList.end();

		for (; StartIter != EndIter; )
		{
			GameEngineCollision* ReleaseCollision = *StartIter;

			if (nullptr == ReleaseCollision)
			{
				MsgAssert("nullptr 인 랜더가 내부에 들어있습니다.");
			}

			if (false == ReleaseCollision->IsDeath())
			{
				++StartIter;
				continue;
			}

			StartIter = CollisionList.erase(StartIter);

			delete ReleaseCollision;
			ReleaseCollision = nullptr;
		}
	}

}

