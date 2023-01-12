#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineResources.h>

Player::Player()
{

}

Player::~Player()
{

}

void Player::Start()
{
	SetPos(GameEngineWindow::GetScreenSize() * 0.5f);
}


void Player::Update()
{
	SetMove(float4::Left * 0.01f);
}

void Player::Render()
{
	float4 PlayerPos = GetPos();

	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("aaaaa.bmp");
	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, 1,PlayerPos, { 100.f, 150.f });
}
