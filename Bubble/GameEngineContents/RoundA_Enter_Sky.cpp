#include "RoundA_Enter_Sky.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "RoundAEnterLevel.h"

RoundA_Enter_Sky::RoundA_Enter_Sky()
{

}

RoundA_Enter_Sky::~RoundA_Enter_Sky()
{

}

void RoundA_Enter_Sky::Start()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	SetPos(ScreenSize.half());

	PivotX = GetPos().x;
	Range = ScreenSize.x * 0.25f;

	SkyRender = CreateRender("RoundA_Enter_Sky.bmp", RoundAEnter_RenderOrder::Sky);
	SkyRender->SetScale({ ScreenSize.x * 1.5f, ScreenSize.y });
}

void RoundA_Enter_Sky::Update(float _DeltaTime)
{
	float4 Pos = GetPos();

	float ExceedLen = static_cast<float>(abs(PivotX - Pos.x) - Range);
	if (0 < ExceedLen)
	{
		Dir *= -1;
		Pos.x += Dir * ExceedLen;
	}

	SetMove(float4::Right * MoveSpeed * _DeltaTime * static_cast<float>(Dir));
}
