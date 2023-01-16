#include "TitleBackGround.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

TitleBackGround::TitleBackGround()
{

}

TitleBackGround::~TitleBackGround()
{

}

void TitleBackGround::Start()
{
	GameEngineRender* Render = nullptr;
	Render = CreateRender("BackGround.bmp", RenderOrder::BackGround);
	Render->SetPosition(GameEngineWindow::GetScreenSize().half());
	Render->SetScale(GameEngineWindow::GetScreenSize());

	Render = CreateRender("BackCurtain.bmp", RenderOrder::BackGround);
	Render->SetPosition(GameEngineWindow::GetScreenSize().half());
	Render->SetScale(GameEngineWindow::GetScreenSize());
	BackCurtain = Render;

	Render = CreateRender("FrontCurtain.bmp", RenderOrder::BackGround);
	Render->SetPosition(GameEngineWindow::GetScreenSize().half());
	Render->SetScale(GameEngineWindow::GetScreenSize());
}

void TitleBackGround::Update(float _DeltaTime)
{
	if (GetLiveTime() < 5.f)
		return;

	float4 BackCurtainPos = BackCurtain->GetPosition();
	BackCurtainPos += float4::Up * 100.f * _DeltaTime;
	BackCurtain->SetPosition(BackCurtainPos);
}
