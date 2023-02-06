#include "BubbleStateIdle.h"
#include <queue>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "BubbleMissle.h"
#include "RoundLevelBase.h"
#include "BubbleMissleFSM.h"

const float BubbleStateIdle::MoveSpeed = 100.f;

BubbleStateIdle::BubbleStateIdle()
{

}

BubbleStateIdle::~BubbleStateIdle()
{

}

void BubbleStateIdle::Init(PlayerCharacterType _CharType, BubbleMissleType _BubbleType)
{
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad();
		IsLoad = true;
	}

	int SelectCharIndex = static_cast<int>(_CharType) * 19;
	int Start = 0;
	int End = 0;

	if (_BubbleType == BubbleMissleType::Normal)
	{
		Start = End = SelectCharIndex;
	}
	else
	{
		Start = SelectCharIndex + (static_cast<int>(_BubbleType) - 1) * 3 + 1;
		End = Start + 2;
	}

	SetAniName("Idle");

	GameEngineRender* Render = GetBubble()->GetRender();
	Render->CreateAnimation
	({
		.AnimationName = GetAniName(),
		.ImageName = "BubbleIdle.bmp",
		.Start = Start,
		.End = End,
		.InterTimer = 0.1f,
	});
}

void BubbleStateIdle::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Bubble");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BubbleIdle.bmp"))->Cut(19, 4);
}



void BubbleStateIdle::Update(float _DeltaTime)
{
	//�÷��̾�� �浹
	if (CollisionWithPlayer())
		return;

	//���� �ö󰡱�
	RaiseBubble(_DeltaTime);
}

//�÷��̾�� �浹
bool BubbleStateIdle::CollisionWithPlayer()
{
	//�� ������ �÷��̾�� �浹��������
	BubbleMissle* ThisBubble = GetBubble();
	GameEngineCollision* CollisionPtr = ThisBubble->GetCollisionPtr();
	if (false == CollisionPtr->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player), }))
		return false;

	//������ �����ϴ� ��� Bubble�� ��������
	auto Bubbles = ThisBubble->GetLevel()->GetActors(static_cast<int>(UpdateOrder::Player_Missle));

	//BFS�� ������ Bubble ��� �Ͷ߸���
	std::queue<BubbleMissle*> BubbleQ;
	BubbleQ.push(ThisBubble);
	ThisBubble->GetFSM()->ChangeState(BubbleStateType::Pop);

	while (BubbleQ.size())
	{
		BubbleMissle* NowBubble =  BubbleQ.front();
		BubbleQ.pop();

		for (size_t i = 0; i < Bubbles.size(); ++i)
		{
			BubbleMissle* NextBubble = dynamic_cast<BubbleMissle*>(Bubbles[i]);
			BubbleMissleFSM* NextFSM = NextBubble->GetFSM();
			if (NextFSM->GetCurStateType() != BubbleStateType::Idle)
				continue;

			float4 NowPos = NowBubble->GetPos();
			float4 NextPos = NextBubble->GetPos();
			float4 BubbleColScale = BubbleMissle::CollisionScale;

			if (false == GameEngineCollision::CollisionCircleToCircle({ NowPos, BubbleColScale }, { NextPos, BubbleColScale }))
				continue;

			NextFSM->ChangeState(BubbleStateType::Pop);
			BubbleQ.push(NextBubble);
		}
	}
	
	return true;
}

void BubbleStateIdle::RaiseBubble(float _DeltaTime)
{
	BubbleMissle* Bubble = GetBubble();
	float4 NowPos = Bubble->GetPos();
	float4 NextPos = NowPos + float4::Up * MoveSpeed * _DeltaTime;

	//�ӽ�
	if (NextPos.y < 100.f)
		return;

	Bubble->SetPos(NextPos);
}
