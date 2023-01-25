#include "EnterRoundCharater.h"
#include <math.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineRender.h>
#include "EnterRoundLevel.h"



EnterRoundCharater::EnterRoundCharater()
{

}

EnterRoundCharater::~EnterRoundCharater()
{

}

void EnterRoundCharater::Start()
{
	BubbleRender = CreateRender("EnterRoundLevel_ClearBubble.bmp", EnterRoundRenderOrder::PlayerBubble);
	BubbleRender->CreateAnimation
	({
		.AnimationName = "Bubble",
		.ImageName = "EnterRoundLevel_ClearBubble.bmp",
		.Start = 0,
		.End = 2,
		.InterTimer = 0.15f
	});

	BubbleRender->SetScale({ 200.f, 200.f });
	BubbleRender->ChangeAnimation("Bubble");
}

void EnterRoundCharater::SetCharacter(int _CharacterIndex)
{
	int CharacterIndex = _CharacterIndex;
	PlayerRender = CreateRender("EnterRoundLevel_Characters.bmp", EnterRoundRenderOrder::Player);
	PlayerRender->CreateAnimation
	({
		.AnimationName = "Player",
		.ImageName = "EnterRoundLevel_Characters.bmp",
		.Start = (CharacterIndex * 4)+ 1,
		.End = (CharacterIndex * 4) + 3,
		.InterTimer = 0.15f
	});

	PlayerRender->SetScale({ 200.f, 200.f });
	PlayerRender->ChangeAnimation("Player");
}

void EnterRoundCharater::Update(float _DeltaTime)
{
	Radian += AddRadian * _DeltaTime;

	float4 Offset;
	Offset.x = static_cast<float>(cos(Radian * GameEngineMath::PIE) * Radius);
	Offset.y = static_cast<float>(-sin(Radian * GameEngineMath::PIE) * Radius);

	PlayerRender->SetPosition(GetPos() + Offset);
	BubbleRender->SetPosition(PlayerRender->GetPosition() + float4::Up * 50.f);
}
