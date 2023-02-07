#include "BubbleStateIdle.h"
#include <queue>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "BubbleMissle.h"
#include "RoundLevelBase.h"
#include "BubbleMissleFSM.h"
#include "RigidBody.h"

const float BubbleStateIdle::MoveSpeed = 100.f;

BubbleStateIdle::BubbleStateIdle()
{
	RigidPtr = new RigidBody;
}

BubbleStateIdle::~BubbleStateIdle()
{
	if (nullptr != RigidPtr)
	{
		delete RigidPtr;
		RigidPtr = nullptr;
	}
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

	//RigidBody와 버블을 연결
	RigidPtr->SetOwner(GetBubble());
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
	//플레이어와 충돌
	if (CollisionWithPlayer())
		return;

	//위로 올라가기
	RaiseBubble(_DeltaTime);

	//충돌체 업데이트(버블의 실질적인 이동)
	RigidPtr->Update(_DeltaTime);

	//이동후 버블들간의 충돌이 발생했는지 확인
	CollisionEachOther();
}

//플레이어와 충돌
bool BubbleStateIdle::CollisionWithPlayer()
{
	//이 버블이 플레이어와 충돌했을때만
	BubbleMissle* ThisBubble = GetBubble();
	GameEngineCollision* CollisionPtr = ThisBubble->GetCollisionPtr();
	if (false == CollisionPtr->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player), }))
		return false;

	//레벨에 존재하는 모든 Bubble을 가져오기
	auto Bubbles = ThisBubble->GetLevel()->GetActors(static_cast<int>(UpdateOrder::Player_Missle));

	//BFS로 인접한 Bubble 모두 터뜨리기
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
			float4 BubbleColScale = BubbleMissle::CollisionScale * 1.2f;

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
	float4 NextVelocity = float4::Up * MoveSpeed;
	float4 NextPos = NowPos + NextVelocity * _DeltaTime;

	//임시
	if (NextPos.y < 100.f)
		return;

	float4 NowVelocity = RigidPtr->GetVelocity();
	RigidPtr->SetVelocity({NowVelocity.x, NextVelocity.y});
}

void BubbleStateIdle::CollisionEachOther()
{
	//버블들끼리 충돌할때만
	GameEngineCollision* CollisionPtr = GetBubble()->GetCollisionPtr();
	std::vector<GameEngineCollision*> Collisions;
	if (false == CollisionPtr->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player_Missle) }, Collisions))
		return;

	GameEngineActor* BubbleActor = GetBubble();
	float4 Pos = GetBubble()->GetPos();
	float4 Velocity = RigidPtr->GetVelocity();
	float4 ReactionDir = float4::Zero;

	for (size_t i = 0; i < Collisions.size(); ++i)
	{
		GameEngineActor* OtherActor = Collisions[i]->GetActor();
		if (OtherActor == BubbleActor)
			continue;

		//반작용방향 += (상대방->자신 방향의 벡터)
		ReactionDir += Pos - OtherActor->GetPos();
	}

	if (true == ReactionDir.IsZero())
		return;

	
	ReactionDir.Normalize();
	float4 ColSize = BubbleMissle::CollisionScale;
	RigidPtr->SetVelocity(ReactionDir * ColSize.Size());
}
