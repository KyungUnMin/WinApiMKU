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

