#include "SelectCharacterBackGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "SelectCharacterLevel.h"

const float4 SelectCharacterBackGround::Offset[4] =
{
	{-1.f, -1.f},
	{1.f, -1.f},
	{-1.f, 1.f},
	{1.f, 1.f}
};

const float	SelectCharacterBackGround::MoveSpeed = 100.f;

SelectCharacterBackGround::SelectCharacterBackGround()
{

}

SelectCharacterBackGround::~SelectCharacterBackGround()
{

}

void SelectCharacterBackGround::Start()
{
	ScreenSize = GameEngineWindow::GetScreenSize();
	SetPos(ScreenSize);

	for (size_t i = 0; i < 4; ++i)
	{
		GameEngineRender* Render = CreateRender("SelectCharacter_CheckPattern.bmp", SelectCharacterRenderOrder::BackGround);
		Render->SetScale(ScreenSize);
		Render->SetPosition(ScreenSize.half() * Offset[i]);
	}
}

void SelectCharacterBackGround::Update(float _DeltaTime)
{
	float4 Dir = ScreenSize.half() * Offset[0];
	float4 NormalDir = Dir.Normalize();
	SetMove(NormalDir * MoveSpeed * _DeltaTime);

	if (GetPos() < float4::Zero)
	{
		SetMove(ScreenSize);
	}
}
