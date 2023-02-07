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
#include "BubbleDestination.h"

//const float BubbleStateIdle::MoveSpeed = 100.f;
const float		BubbleStateIdle::MoveSpeed = 10.f;
const float4	BubbleStateIdle::MaxVelocity = float4{ 100.f, 100.f };

BubbleStateIdle::BubbleStateIdle()
{
	RigidPtr = new RigidBody;
	RigidPtr->SetMaxVelocity(MaxVelocity);
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

	CreateAnimation(_CharType, _BubbleType);

	//RigidBody�� ������ ����
	RigidPtr->SetOwner(GetBubble());

	//�� ������ �����ϴ� BubbleDestination�� BubbleDests�� ����
	PutDest();
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

void BubbleStateIdle::CreateAnimation(PlayerCharacterType _CharType, BubbleMissleType _BubbleType)
{
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

void BubbleStateIdle::PutDest()
{
	std::vector<GameEngineActor*> Actors = GetBubble()->GetLevel()->GetActors(UpdateOrder::BubbleDest);
	BubbleDests.reserve(Actors.size());

	for (GameEngineActor* Actor : Actors)
	{
		BubbleDestination* Dest = dynamic_cast<BubbleDestination*>(Actor);
		if (nullptr == Dest)
		{
			MsgAssert("UpdateOrder::BubbleDest �׷쿡 BubbleDest�� �ƴ� Actor�� ���ԵǾ� �ֽ��ϴ�");
			return;
		}

		BubbleDests.push_back(Dest);
	}
}



void BubbleStateIdle::EnterState()
{
	BubbleMissleStateBase::EnterState();

	//���� ����� BubbleDest�� ��ġ�� ������ ����
	float MinDistance = FLT_MAX;
	float4 NowPos = GetBubble()->GetPos();

	for (BubbleDestination* Dest : BubbleDests)
	{
		float4 DestPos = Dest->GetPos();
		float Distance = (DestPos - NowPos).Size();

		if (MinDistance <= Distance)
			continue;

		MinDistance = Distance;
		NowDest = Dest;
	}
}


void BubbleStateIdle::Update(float _DeltaTime)
{
	//�÷��̾�� �浹
	if (CollisionWithPlayer())
		return;

	//�̵�
	MoveBubble(_DeltaTime);

	//�������� �����ߴ��� Ȯ��
	CheckDest();

	//�浹ü ������Ʈ(������ �������� �̵�)
	RigidPtr->Update(_DeltaTime);

	//�̵��� ����鰣�� �浹�� �߻��ߴ��� Ȯ��
	CollisionEachOther();
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
			float4 BubbleColScale = BubbleMissle::CollisionScale * 1.2f;

			if (false == GameEngineCollision::CollisionCircleToCircle({ NowPos, BubbleColScale }, { NextPos, BubbleColScale }))
				continue;

			NextFSM->ChangeState(BubbleStateType::Pop);
			BubbleQ.push(NextBubble);
		}
	}
	
	return true;
}

void BubbleStateIdle::MoveBubble(float _DeltaTime)
{
	BubbleMissle* Bubble = GetBubble();
	float4 NowPos = Bubble->GetPos();
	float4 DestPos = NowDest->GetPos();

	float4 Dir = DestPos - NowPos;
	Dir.Normalize();

	float4 NextVelocity = Dir * MoveSpeed;
	RigidPtr->AddVelocity(NextVelocity);
}

void BubbleStateIdle::CheckDest()
{
	size_t NowStage = GetBubble()->GetRoundLevel()->GetNowStage();
	float4 BubblePos = GetBubble()->GetPos();
	float4 BubbleScale = BubbleMissle::CollisionScale;

	for (BubbleDestination* Dest : BubbleDests)
	{
		if (Dest->GetStageIndex() != NowStage)
			continue;

		if (nullptr == Dest->GetNextDest())
			continue;

		if (Dest != NowDest)
			continue;

		float4 DestPos = Dest->GetPos();
		float4 DestScale = BubbleDestination::CollisionScale;
		
		if (false == GameEngineCollision::CollisionCircleToCircle({ BubblePos, BubbleScale }, { DestPos, DestScale }))
			continue;

		NowDest = NowDest->GetNextDest();
	}
}

void BubbleStateIdle::CollisionEachOther()
{
	//����鳢�� �浹�Ҷ���
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

		//���ۿ���� += (����->�ڽ� ������ ����)
		ReactionDir += Pos - OtherActor->GetPos();
	}

	if (true == ReactionDir.IsZero())
		return;

	
	ReactionDir.Normalize();
	float4 ColSize = BubbleMissle::CollisionScale;
	RigidPtr->SetVelocity(ReactionDir * ColSize.Size());
}
