#include "EnterRoundBubble.h"
#include <math.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "EnterRoundLevel.h"

EnterRoundBubble::EnterRoundBubble()
{
	//거품 생성기의 6개 각도 설정
	for (size_t i = 0; i < 6; ++i)
	{
		//(2파이 / 6) * i
		Dir[i] = (2.f / 6.f) * static_cast<float>(i);
	}
}

EnterRoundBubble::~EnterRoundBubble()
{

}


void EnterRoundBubble::Start()
{
	//중앙으로 이동
	SetPos(GameEngineWindow::GetScreenSize().half());
	//10초간 생성될 거품의 vector공간을 미리 만든다
	Bubbles.reserve(100);
}

void EnterRoundBubble::Update(float _DeltaTime)
{
	//지금까지 생성되었던 거품을 이동시킨다
	BubbleMove(_DeltaTime);

	//지금까지 생성되었던 거품의 크기를 증가시킨다
	BubbleScaleUp(_DeltaTime);

	//거품 생성기의 6방향 각도를 조금씩 변환
	for (size_t i = 0; i < 6; ++i)
	{
		Dir[i] += RotateSpeed * _DeltaTime;
	}

	//거품 생성 주기마다 SpawnIndex방향에서 거품을 생성
	AccTime += _DeltaTime;
	if (AccTime < BubbleSpawnTime)
		return;

	AccTime = 0.0f;
	BubbleCreate(Dir[SpawnIndex++]);
	SpawnIndex %= 6;
}


//지금까지 생성되었던 거품을 이동
void EnterRoundBubble::BubbleMove(float _DeltaTime)
{
	for (size_t i = 0; i < Bubbles.size(); ++i)
	{
		float Radian = Bubbles[i].first;
		GameEngineRender* Bubble = Bubbles[i].second;

		float4 NextVec;
		NextVec.x = static_cast<float>(cos(Radian * GameEngineMath::PIE) * MoveSpeed);
		NextVec.y = static_cast<float>(-sin(Radian * GameEngineMath::PIE) * MoveSpeed);

		float4 Pos = Bubble->GetPosition();
		Bubble->SetPosition(Pos + NextVec * _DeltaTime);
	}
}

//지금까지 생성되었던 거품의 크기를 증가
void EnterRoundBubble::BubbleScaleUp(float _DeltaTime)
{
	for (size_t i = 0; i < Bubbles.size(); ++i)
	{
		GameEngineRender* Bubble = Bubbles[i].second;
		float4 Scale = Bubble->GetScale();
		Scale += float4{ 1.f, 1.f } *BubbleGrowSpeed * _DeltaTime;

		if (BubbleMaxScale < Scale)
			continue;

		Bubble->SetScale(Scale);
	}
}

// 거품을 생성
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

	BubbleRender->SetScale(float4::Zero);
	BubbleRender->ChangeAnimation("Bubble");
	Bubbles.push_back(std::make_pair(_DirRadian, BubbleRender));
}

//생성된 거품들을 모두 지우고 vector를 clear
void EnterRoundBubble::Reset()
{
	for (auto Pair : Bubbles)
	{
		Pair.second->Death();
	}

	Bubbles.clear();
}
