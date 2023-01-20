#include "BackGround.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

BackGround::BackGround()
{
	SetPos(GameEngineWindow::GetScreenSize().half());
}

BackGround::~BackGround()
{
	
}

GameEngineRender* BackGround::CreateRender(const std::string_view& _Image, int _Order)
{
	GameEngineRender* Render = GameEngineActor::CreateRender(_Image, _Order);
	Render->SetScale(GameEngineWindow::GetScreenSize());
	BackGroundRenders.push_back(Render);
	return Render;
}

GameEngineRender* BackGround::GetRender(size_t _Index)
{
	if (BackGroundRenders.size() <= _Index)
	{
		MsgAssert("해당 렌더 벡터의 인덱스 범위를 넘어서 접근하였습니다");
		return nullptr;
	}

	return BackGroundRenders[_Index];
}
