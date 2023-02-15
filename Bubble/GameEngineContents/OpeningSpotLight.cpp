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
	//생성 및 크기 위치 설정
	GameEngineRender* Render = CreateRender("Opening_SpotLight.bmp", OpeningRenderOrder::SpotLight);
	Render->SetScale(GameEngineWindow::GetScreenSize() * 3.5f);
	Render->SetAlpha(200);
	SetPos(GameEngineWindow::GetScreenSize().half());
}

void OpeningSpotLight::Update(float _DeltaTime)
{
	//현재위치
	float4 NowPos = GetPos();

	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	//다음 위치
	float4 NextPos = NowPos + Dir * MoveSpeed * _DeltaTime;

	//StopTime 보다 시간이 더 지났다면 StopPos로 위치를 고정
	if (StopTime < GetLiveTime())
	{
		NextPos = StopPos;
	}

	//현재 위치가 스크린 밖으로 나가지 않고 시간이 OutTime 이전이라면 NextPos로 이동
	if ((0.f < NextPos.x
		&& NextPos.x < ScreenSize.x
		&& 0.f < NextPos.y
		&& NextPos.y < ScreenSize.y)
		|| OutTime < GetLiveTime())
	{
		SetPos(NextPos);
		return;
	}

	//벡터의 방향 바꾸기
	if (NextPos.y < 0.f || ScreenSize.y < NextPos.y)
		Dir.y *= -1;
	else
		Dir.x *= -1;
}
