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
	//�ִϸ��̼� ����
	BubbleMissleStateBase::EnterState();

	//���� ����� BubbleDest�� ��ġ�� ������ ����
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
	//���� ����ð��� �������� Pop���� ����
	if (true == DryPopCheck())
		return;

	//�÷��̾�� �浹 ���� Ȯ��
	PlayerCollisionCheck();

	//�̵�
	MoveBubble(_DeltaTime);

	//ȭ�� ������ �����ٸ� �ݴ������� ��ġ ����(���͸� ��� �ִ� ������ ��쿡��)
	CycleScreenOut();

	//�� ���� �ȿ� ���Ͱ� �����ִٸ� ������ ��ġ�� �ڽ��� ��ġ�� ����
	DragMonster();

	//�������� �����ߴ��� Ȯ��
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

	//��ũ�� �ȿ� �����ϴ� ��쿣 �ƹ��ϵ� �Ͼ�� ����
	if ((-Offset <= BubblePos.y) && (BubblePos.y < ScreenSize.y + Offset))
		return;

	//���Ͱ� ���� ������ ��쿣 ���ֱ�
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

	//���� ���������� Ȱ��ȭ�Ǿ��ִ� BubbleDest���� �����´�
	RoundLevelBase* RoundLevel = GetBubble()->GetRoundLevel();
	size_t NowStage = RoundLevel->GetNowStage();
	BubbleDestHelper* BDHelper = RoundLevel->GetBubbleDestHelper();
	const std::vector<BubbleDestination*>& BubbleDests = BDHelper->GetBubbleDest(NowStage);

	float4 BubblePos = GetBubble()->GetPos();
	float4 BubbleScale = BubbleMissle::CollisionScale;

	for (BubbleDestination* Dest : BubbleDests)
	{
		//���� ���������� ��������
		if (Dest->GetStageIndex() != NowStage)
			continue;

		//���� ������ �������� ���ؼ���
		if (Dest != NowDest)
			continue;

		float4 DestPos = Dest->GetPos();
		float4 DestScale = BubbleDestination::CollisionScale;
		
		//�������� �� ������ �浹�Ѵٸ�
		if (false == GameEngineCollision::CollisionCircleToCircle({ BubblePos, BubbleScale }, { DestPos, DestScale }))
			return;

		//������ �̵��� �������� �����Ѵٸ� �� ������ ������ ����
		if (nullptr != Dest->GetNextDest())
		{
			NowDest = NowDest->GetNextDest();
			return;
		}

		//���� �������� �����ߴٸ� Idle ���·� ����
		GetFSM()->ChangeState(BubbleStateType::Idle);
		return;
	}
}
