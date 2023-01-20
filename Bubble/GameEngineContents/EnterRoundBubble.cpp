#include "EnterRoundBubble.h"
#include <math.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "EnterRoundLevel.h"

EnterRoundBubble::EnterRoundBubble()
{
	for (size_t i = 0; i < 6; ++i)
	{
		Dir[i] = (2.f / 6.f) * static_cast<float>(i);
	}
}

EnterRoundBubble::~EnterRoundBubble()
{

}

void EnterRoundBubble::Start()
{
	SetPos(GameEngineWindow::GetScreenSize().half());
	Bubbles.reserve(10000);
}

void EnterRoundBubble::Update(float _DeltaTime)
{
	AccTime += _DeltaTime;
	if(BubbleSpawnTime < AccTime)
	{
		AccTime = 0.0f;
		for (size_t i = 0; i < 6; ++i)
		{
			BubbleCreate(Dir[i]);
		}
	}

	for (size_t i = 0; i < 6; ++i)
	{
		BubbleMove(_DeltaTime);
		Dir[i] += RotateSpeed * _DeltaTime;
	}
}

void EnterRoundBubble::BubbleMove(float _DeltaTime)
{
	for (size_t i = 0; i < Bubbles.size(); ++i)
	{
		float Radian = Bubbles[i].first;
		GameEngineRender* Bubble = Bubbles[i].second;

		float4 NextVec;
		NextVec.x = cos(Radian * GameEngineMath::PIE) * MoveSpeed;
		NextVec.y = -sin(Radian * GameEngineMath::PIE) * MoveSpeed;

		float4 Pos = Bubble->GetPosition();
		Bubble->SetPosition(Pos + NextVec * _DeltaTime);
	}
}

void EnterRoundBubble::BubbleCreate(float _DirRadian)
{
	GameEngineRender* BubbleRender = CreateRender("EnterRoundLevel_ClearBubble.bmp", EnterRoundRenderOrder::Bubble);
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
	Bubbles.push_back(std::make_pair(_DirRadian, BubbleRender));
}
