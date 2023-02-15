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
	//���� �� ũ�� ��ġ ����
	GameEngineRender* Render = CreateRender("Opening_SpotLight.bmp", OpeningRenderOrder::SpotLight);
	Render->SetScale(GameEngineWindow::GetScreenSize() * 3.5f);
	Render->SetAlpha(200);
	SetPos(GameEngineWindow::GetScreenSize().half());
}

void OpeningSpotLight::Update(float _DeltaTime)
{
	//������ġ
	float4 NowPos = GetPos();

	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	//���� ��ġ
	float4 NextPos = NowPos + Dir * MoveSpeed * _DeltaTime;

	//StopTime ���� �ð��� �� �����ٸ� StopPos�� ��ġ�� ����
	if (StopTime < GetLiveTime())
	{
		NextPos = StopPos;
	}

	//���� ��ġ�� ��ũ�� ������ ������ �ʰ� �ð��� OutTime �����̶�� NextPos�� �̵�
	if ((0.f < NextPos.x
		&& NextPos.x < ScreenSize.x
		&& 0.f < NextPos.y
		&& NextPos.y < ScreenSize.y)
		|| OutTime < GetLiveTime())
	{
		SetPos(NextPos);
		return;
	}

	//������ ���� �ٲٱ�
	if (NextPos.y < 0.f || ScreenSize.y < NextPos.y)
		Dir.y *= -1;
	else
		Dir.x *= -1;
}
