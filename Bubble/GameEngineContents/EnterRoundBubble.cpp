#include "EnterRoundBubble.h"
#include <math.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "EnterRoundLevel.h"

EnterRoundBubble::EnterRoundBubble()
{
	//��ǰ �������� 6�� ���� ����
	for (size_t i = 0; i < 6; ++i)
	{
		//(2���� / 6) * i
		Dir[i] = (2.f / 6.f) * static_cast<float>(i);
	}
}

EnterRoundBubble::~EnterRoundBubble()
{

}


void EnterRoundBubble::Start()
{
	//�߾����� �̵�
	SetPos(GameEngineWindow::GetScreenSize().half());
	//10�ʰ� ������ ��ǰ�� vector������ �̸� �����
	Bubbles.reserve(100);
}

void EnterRoundBubble::Update(float _DeltaTime)
{
	//���ݱ��� �����Ǿ��� ��ǰ�� �̵���Ų��
	BubbleMove(_DeltaTime);

	//���ݱ��� �����Ǿ��� ��ǰ�� ũ�⸦ ������Ų��
	BubbleScaleUp(_DeltaTime);

	//��ǰ �������� 6���� ������ ���ݾ� ��ȯ
	for (size_t i = 0; i < 6; ++i)
	{
		Dir[i] += RotateSpeed * _DeltaTime;
	}

	//��ǰ ���� �ֱ⸶�� SpawnIndex���⿡�� ��ǰ�� ����
	AccTime += _DeltaTime;
	if (AccTime < BubbleSpawnTime)
		return;

	AccTime = 0.0f;
	BubbleCreate(Dir[SpawnIndex++]);
	SpawnIndex %= 6;
}


//���ݱ��� �����Ǿ��� ��ǰ�� �̵�
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

//���ݱ��� �����Ǿ��� ��ǰ�� ũ�⸦ ����
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

// ��ǰ�� ����
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

//������ ��ǰ���� ��� ����� vector�� clear
void EnterRoundBubble::Reset()
{
	for (auto Pair : Bubbles)
	{
		Pair.second->Death();
	}

	Bubbles.clear();
}
