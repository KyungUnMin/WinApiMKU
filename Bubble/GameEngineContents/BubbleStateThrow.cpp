#include "BubbleStateThrow.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "BubbleMissle.h"
#include "BubbleMissleFSM.h"
#include "RoundLevelBase.h"
#include "MonsterBase.h"

const float BubbleStateThrow::MoveSpeed = 500.f;

BubbleStateThrow::BubbleStateThrow()
{

}

BubbleStateThrow::~BubbleStateThrow()
{

}

void BubbleStateThrow::Init(PlayerCharacterType _CharType, BubbleMissleType _BubbleType)
{
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad();
		IsLoad = true;
	}

	int Index = static_cast<int>(_CharType) * 6;
	SetAniName("Throw");

	GameEngineRender* Render = GetBubble()->GetRender();
	Render->CreateAnimation
	({
		.AnimationName = GetAniName(),
		.ImageName = "BubbleThrow.bmp",
		.Start = Index,
		.End = Index + 5,
		.InterTimer = 0.1f,
		.Loop = false
	});
}

void BubbleStateThrow::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Bubble");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BubbleThrow.bmp"))->Cut(6, 4);
}



void BubbleStateThrow::Update(float _DeltaTime)
{
	BubbleMissle* Bubble = GetBubble();
	if (true == Bubble->GetRender()->IsAnimationEnd())
	{
		GetFSM()->ChangeState(BubbleStateType::Move);
		return;
	}

	float4 NowPos = Bubble->GetPos();
	float4 MoveDir = Bubble->GetDirVec();
	float4 NextPos = NowPos + (MoveDir * MoveSpeed * _DeltaTime);
	float4 Offset = MoveDir * BubbleMissle::CollisionScale.hx();

	if (Bubble->GetRoundLevel()->IsBlockPos(NextPos + Offset))
	{
		GetFSM()->ChangeState(BubbleStateType::Move);
		return;
	}

	if (true == MonsterCollisionCheck())
	{
		GetFSM()->ChangeState(BubbleStateType::Move);
		return;
	}


	Bubble->SetPos(NextPos);
}

bool BubbleStateThrow::MonsterCollisionCheck()
{
	std::vector<GameEngineCollision*> Monsters;
	GameEngineCollision* CollisionPtr = GetBubble()->GetCollisionPtr();
	if (false == CollisionPtr->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Monster) }, Monsters))
		return false;

	GameEngineActor* MonsterActor = Monsters.front()->GetActor();
	MonsterBase* Monster = dynamic_cast<MonsterBase*>(MonsterActor);
	if (nullptr == Monster)
	{
		MsgAssert("CollisionOrder::Monster에 몬스터가 아닌 객체가 들어가있습니다");
		return false;
	}

	Monster->AttackedBubble();
	GetBubble()->SetLockMonster(Monster);
	return true;
}


