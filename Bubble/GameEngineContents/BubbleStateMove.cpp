#include "BubbleStateMove.h"
#include <queue>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "BubbleMissle.h"
#include "RoundLevelBase.h"
#include "BubbleMissleFSM.h"
#include "BubbleDestHelper.h"
#include "BubbleDestination.h"

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

	BubbleMissleStateBase::CheckNormalBubble(_BubbleType);

	CreateAnimation(_CharType, _BubbleType);
	ScreenSize = GameEngineWindow::GetScreenSize();

	/*if (PlayerCharacterType::CORORON == _CharType)
	{
		MoveSpeed = 150.f;
	}*/
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

	//가장 가까운 BubbleDest의 위치로 목적지 설정
	FindCloseDest();
}


void BubbleStateMove::FindCloseDest()
{
	RoundLevelBase* RoundLevel = GetBubble()->GetRoundLevel();
	BubbleDestHelper* BDHelper = RoundLevel->GetBubbleDestHelper();
	const std::vector<BubbleDestination*>& BubbleDests = BDHelper->GetBubbleDest(RoundLevel->GetNowStage());

	if (true == BubbleDests.empty())
		return;

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
	//버블 경과시간이 지났을때 Pop으로 변경
	if (true == DryPopCheck())
		return;

	//플레이어와 충돌 여부 확인
	PlayerCollisionCheck();

	//이동
	MoveBubble(_DeltaTime);

	//화면 밖으로 나갔다면 반대편으로 위치 설정(몬스터를 잡고 있는 버블의 경우에만)
	CycleScreenOut();

	//이 버블 안에 몬스터가 갇혀있다면 몬스터의 위치를 자신의 위치로 변경
	DragMonster();

	//목적지에 도착했는지 확인
	CheckDest();
}


void BubbleStateMove::MoveBubble(float _DeltaTime)
{
	BubbleMissle* Bubble = GetBubble();
	float4 NowPos = Bubble->GetPos();

	if (nullptr == NowDest)
	{
		GetBubble()->SetMove(float4::Up * MoveSpeed * _DeltaTime);
		return;
	}

	float4 DestPos = NowDest->GetPos();

	float4 Dir = DestPos - NowPos;
	Dir.Normalize();

	GetBubble()->SetMove(Dir * MoveSpeed * _DeltaTime);
}




void BubbleStateMove::CycleScreenOut()
{
	static const float Offset = 10.f;
	float4 BubblePos = GetBubble()->GetPos();

	//스크린 안에 존재하는 경우엔 아무일도 일어나지 않음
	if ((-Offset <= BubblePos.y) && (BubblePos.y < ScreenSize.y + Offset))
		return;

	//몬스터가 없는 버블의 경우엔 없애기
	if (nullptr == GetBubble()->GetCatchTarget())
	{
		GetBubble()->Death();
		return;
	}

	if (BubblePos.y < 0)
	{
		BubblePos.y = ScreenSize.y;
	}
	else if (ScreenSize.y < BubblePos.y)
	{
		BubblePos.y = 0.f;
	}

	GetBubble()->SetPos(BubblePos);
	FindCloseDest();
}






void BubbleStateMove::CheckDest()
{
	if (nullptr == NowDest)
		return;

	//현재 스테이지에 활성화되어있는 BubbleDest들을 가져온다
	RoundLevelBase* RoundLevel = GetBubble()->GetRoundLevel();
	size_t NowStage = RoundLevel->GetNowStage();
	BubbleDestHelper* BDHelper = RoundLevel->GetBubbleDestHelper();
	const std::vector<BubbleDestination*>& BubbleDests = BDHelper->GetBubbleDest(NowStage);

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
