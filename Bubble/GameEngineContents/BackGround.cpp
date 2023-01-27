#include "BackGround.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

BackGround::BackGround()
{
	//이 객체는 배경이 될 예정이기 때문에 항상 스크린의 중심에 위치
	SetPos(GameEngineWindow::GetScreenSize().half());
}

BackGround::~BackGround()
{
	
}

GameEngineRender* BackGround::CreateRender(const std::string_view& _Image, int _Order)
{
	//렌더링 생성
	GameEngineRender* Render = GameEngineActor::CreateRender(_Image, _Order);

	//항상 렌더링 이미지는 스크린 크기만큼
	Render->SetScale(GameEngineWindow::GetScreenSize());

	//자료구조에 저장
	BackGroundRenders.push_back(Render);
	return Render;
}

GameEngineRender* BackGround::GetRender(size_t _Index)
{
	//예외처리
	if (BackGroundRenders.size() <= _Index)
	{
		MsgAssert("해당 렌더 벡터의 인덱스 범위를 넘어서 접근하였습니다");
		return nullptr;
	}

	return BackGroundRenders[_Index];
}
