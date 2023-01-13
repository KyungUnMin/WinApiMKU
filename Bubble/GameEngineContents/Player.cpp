#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::Start()
{
	SetPos(GameEngineWindow::GetScreenSize() * 0.5f);

	GameEngineRender* Render1 = CreateRender("aaaaa.bmp", RenderOrder::Map);
	Render1->SetScale({ 100, 100 });
	Render1->SetPosition({ -100, 100 });


	GameEngineRender* Render2 = CreateRender("aaaaa.bmp", RenderOrder::Map);
	Render2->SetScale({ 100, 100 });
	Render2->SetPosition({ 100, 100 });

	Image = GameEngineResources::GetInst().ImageFind("aaaaa.bmp");
}


void Player::Update(float _DeltaTime)
{
	AccTime += _DeltaTime;
	if (0.5f < AccTime)
		return;

	AccTime -= 0.5f;
	++NowFrame;

	if (false == Image->IsCutIndexValid(NowFrame))
	{
		NowFrame = 0;
	}
}

void Player::Render(float _DeltaTime)
{
	float4 PlayerPos = GetPos();

	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, NowFrame,PlayerPos, { 100.f, 150.f });
}
