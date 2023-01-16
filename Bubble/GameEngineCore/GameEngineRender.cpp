#include "GameEngineRender.h"
#include <GameEngineCore/GameEngineResources.h>
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>

GameEngineRender::GameEngineRender()
{

}

GameEngineRender::~GameEngineRender()
{

}


//GameEngineResources에서 이미지 찾아오기
void GameEngineRender::SetImage(const std::string_view& _ImageName)
{
	Image = GameEngineResources::GetInst().ImageFind(_ImageName);
}




//렌더링 되는 순서 결정 및 Level의 Renders에 등록(Actor에서만 호출)
void GameEngineRender::SetOrder(int _Order)
{
	Order = _Order;

	//GameEngineLevel의 Renders에 등록
	Owner->GetLevel()->PushRender(this);
}



void GameEngineRender::SetFrame(int _Frame)
{
	if (nullptr == Image)
	{
		MsgAssert("이미지가 존재하지 않는 랜더러에 프레임을 지정하려고 했습니다.");
	}

	if (false == Image->IsImageCutting())
	{
		MsgAssert("잘려있는 이미지만 프레임을 지정해줄 수 있습니다.");
	}

	if (false == Image->IsCutIndexValid(_Frame))
	{
		MsgAssert("유요하지 않은 이미지인덱스 입니다.");
	}

	Frame = _Frame;
}



//Level의 Render를 통해 실제 렌더링되는 함수
void GameEngineRender::Render(float _DeltaTime)
{
	//오프셋이 적용된 렌더링 될 위치
	float4 RenderPos = Owner->GetPos() + Position;

	//이미지를 자른 경우
	if (true == Image->IsImageCutting())
	{
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, Frame, RenderPos, Scale);
	}

	//이미지를 자르지 않은 경우엔 리소스 전체크기를 출력
	else
	{
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, RenderPos, Scale, {0.f, 0.f}, Image->GetImageScale());
	}
}
