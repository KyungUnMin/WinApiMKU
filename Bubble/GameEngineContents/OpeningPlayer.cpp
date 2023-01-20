#include "OpeningPlayer.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "OpeningLevel.h"

OpeningPlayer::OpeningPlayer()
{

}

OpeningPlayer::~OpeningPlayer()
{

}

void OpeningPlayer::Start()
{
	GameEngineRender* Render = CreateRender("Opening_Player.bmp", OpeningRenderOrder::Player);

	Render->CreateAnimation
	({
		.AnimationName = "PlayerHello",
		.ImageName = "Opening_Player.bmp",
		.Start = 0,
		.End = 6,
		.InterTimer = 0.2f
	});

	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	Render->SetScale({ScreenSize.x * 0.12f, ScreenSize.y * 0.18f });
	SetPos({ ScreenSize.x * 0.5f, ScreenSize.y * 0.9f });

	Render->ChangeAnimation("PlayerHello");
}
