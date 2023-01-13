#include "GameEngineActor.h"
#include "GameEngineRender.h"

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
	Render->Owner = this;
	Render->SetOrder(_Order);
	RenderList.push_back(Render);
	return Render;
}

