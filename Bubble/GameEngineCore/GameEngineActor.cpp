#include "GameEngineActor.h"
#include "GameEngineRender.h"
#include "GameEngineLevel.h"

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


GameEngineLevel* GameEngineActor::GetLevel()
{
	return GetOwner<GameEngineLevel>();
}

//CreateRender(int _Order)�� ���� �� �̹��� ��������
GameEngineRender* GameEngineActor::CreateRender(const std::string_view& _Image, int _Order)
{
	GameEngineRender* Render = CreateRender(_Order);
	Render->SetImage(_Image);
	return Render;
}

//GameEngineRender�� ���� �� �����ϰ� Level�� RenderList�� ���
GameEngineRender* GameEngineActor::CreateRender(int _Order)
{
	GameEngineRender* Render = new GameEngineRender;
	Render->SetOwner(this);
	Render->SetOrder(_Order);
	RenderList.push_back(Render);
	return Render;
}
