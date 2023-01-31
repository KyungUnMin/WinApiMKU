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

	//총 4개의 렌더러가 존재
	//이 actor를 기준으로 1234분면처럼 존재
	for (size_t i = 0; i < 4; ++i)
	{
		GameEngineRender* Render = CreateRender("SelectCharacter_CheckPattern.bmp", SelectCharacterRenderOrder::BackGround);
		Render->SetScale(ScreenSize);
		Render->SetPosition(ScreenSize.half() * Offset[i]);
	}
}

void SelectCharacterBackGround::Update(float _DeltaTime)
{
	//vector(-해상도.x, -해상도.y) 방향으로 이동
	float4 Dir = ScreenSize.half() * Offset[0];
	Dir.Normalize();
	SetMove(Dir * MoveSpeed * _DeltaTime);

	//이 Actor의 위치가 (0,0)보다 작다면 스크린 크기만큼 이동
	if (GetPos() < float4::Zero)
	{
		SetMove(ScreenSize);
	}
}
