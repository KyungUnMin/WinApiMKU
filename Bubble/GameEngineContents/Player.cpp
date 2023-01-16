#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"
#include <GameEnginePlatform/GameEngineInput.h>

Player::Player()
{

}

Player::~Player()
{

}

void Player::Start()
{
	SetPos(GameEngineWindow::GetScreenSize() * 0.5f);

	Render1 = CreateRender("aaaaa.bmp", RenderOrder::Map);
	Render1->SetScale({ 100, 100 });
	Render1->SetPosition({ -100, 100 });
	


	Render2 = CreateRender("aaaaa.bmp", RenderOrder::Map);
	Render2->SetScale({ 100, 100 });
	Render2->SetPosition({ 100, 100 });

	GameEngineInput::CreateKey("PlayerOnOff", 'K');

	//Image = GameEngineResources::GetInst().ImageFind("aaaaa.bmp");
}


void Player::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("PlayerOnOff"))
	{
		Render1->OnOffSwtich();
		Render2->OnOffSwtich();
	}
}

