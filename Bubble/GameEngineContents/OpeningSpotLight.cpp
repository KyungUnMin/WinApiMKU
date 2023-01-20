#include "OpeningSpotLight.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "OpeningLevel.h"

OpeningSpotLight::OpeningSpotLight()
{

}

OpeningSpotLight::~OpeningSpotLight()
{

}

void OpeningSpotLight::Start()
{
	GameEngineRender* Render = CreateRender("Opening_SpotLight.bmp", OpeningRenderOrder::SpotLight);
	Render->SetScale(GameEngineWindow::GetScreenSize() * 3.5f);
	SetPos(GameEngineWindow::GetScreenSize().half());
}

void OpeningSpotLight::Update(float _DeltaTime)
{
	float4 NowPos = GetPos();

	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	float4 NextPos = NowPos + Dir * MoveSpeed * _DeltaTime;

	if (StopTime < GetLiveTime())
	{
		NextPos = StopPos;
	}

	if ((0.f < NextPos.x
		&& NextPos.x < ScreenSize.x
		&& 0.f < NextPos.y
		&& NextPos.y < ScreenSize.y)
		|| OutTime < GetLiveTime())
	{
		SetPos(NextPos);
		return;
	}

	if (NextPos.y < 0.f || ScreenSize.y < NextPos.y)
		Dir.y *= -1;
	else
		Dir.x *= -1;
}
