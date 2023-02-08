#include "BubbleStateMove.h"
#include <queue>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "BubbleMissle.h"
#include "RoundLevelBase.h"
#include "BubbleMissleFSM.h"
#include "BubbleDestination.h"

const float		BubbleStateMove::MoveSpeed = 100.f;

BubbleStateMove::BubbleStateMove()
{
}

BubbleStateMove::~BubbleStateMove()
{

}

void BubbleStateMove::Init(PlayerCharacterType _CharType, BubbleMissleType _BubbleType)
{
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad();
		IsLoad = true;
	}

	CreateAnimation(_CharType, _BubbleType);
}

void BubbleStateMove::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Bubble");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BubbleIdle.bmp"))->Cut(19, 4);
}

void BubbleStateMove::CreateAnimation(PlayerCharacterType _CharType, BubbleMissleType _BubbleType)
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

	SetAniName("Move");

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


void BubbleStateMove::EnterState()
{
	//애니메이션 변경
	BubbleMissleStateBase::EnterState();

	//충돌체 켜기
	GetBubble()->GetCollisionPtr()->On();

	//가장 가까운 BubbleDest의 위치로 목적지 설정
	RoundLevelBase* RoundLevel = GetBubble()->GetRoundLevel();
	const std::vector<BubbleDestination*>& BubbleDests = RoundLevel->GetBubbleDest(RoundLevel->GetNowStage());

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


void BubbleStateMove::Update(float _DeltaTime)
{
	//이동
	MoveBubble(_DeltaTime);

	//목적지에 도착했는지 확인
	CheckDest();
}



void BubbleStateMove::MoveBubble(float _DeltaTime)
{
	BubbleMissle* Bubble = GetBubble();
	float4 NowPos = Bubble->GetPos();
	float4 DestPos = NowDest->GetPos();

	float4 Dir = DestPos - NowPos;
	Dir.Normalize();

	GetBubble()->SetMove(Dir * MoveSpeed * _DeltaTime);
}

void BubbleStateMove::CheckDest()
{
	//현재 스테이지에 활성화되어있는 BubbleDest들을 가져온다
	RoundLevelBase* RoundLevel = GetBubble()->GetRoundLevel();
	size_t NowStage = RoundLevel->GetNowStage();
	const std::vector<BubbleDestination*>& BubbleDests = RoundLevel->GetBubbleDest(NowStage);

	float4 BubblePos = GetBubble()->GetPos();
	float4 BubbleScale = BubbleMissle::CollisionScale;

	for (BubbleDestination* Dest : BubbleDests)
	{
		//현재 스테이지의 목적지만
		if (Dest->GetStageIndex() != NowStage)
			continue;

		//지금 가려는 목적지에 대해서만
		if (Dest != NowDest)
			continue;

		float4 DestPos = Dest->GetPos();
		float4 DestScale = BubbleDestination::CollisionScale;
		
		//목적지와 이 버블이 충돌한다면
		if (false == GameEngineCollision::CollisionCircleToCircle({ BubblePos, BubbleScale }, { DestPos, DestScale }))
			return;

		//다음에 이동할 목적지가 존재한다면 그 곳으로 목적지 변경
		if (nullptr != Dest->GetNextDest())
		{
			NowDest = NowDest->GetNextDest();
			return;
		}

		//최종 목적지에 도달했다면 Idle 상태로 변경
		GetFSM()->ChangeState(BubbleStateType::Idle);
		return;
	}
}
