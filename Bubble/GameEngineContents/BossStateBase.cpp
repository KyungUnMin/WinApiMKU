#include "BossStateBase.h"
#include <string>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "BossMonsterFSM.h"
#include "BossMonster.h"
#include "PlayerBase.h"
#include "NatureMissleBase.h"
#include "BossHpBar.h"

BossStateBase::BossStateBase()
{
}

BossStateBase::~BossStateBase()
{
}


BossMonster* BossStateBase::GetBoss()
{
	return FsmPtr->GetBoss();
}


void BossStateBase::ChangeAniDir(const std::string_view& _AniName)
{
	BossMonster* BossPtr = FsmPtr->GetBoss();
	GameEngineRender* RenderPtr = BossPtr->GetRender();

	std::string NextAniName = BossPtr->GetDirStr();
	NextAniName += _AniName;
	RenderPtr->ChangeAnimation(NextAniName, true);
}

void BossStateBase::CheckCollisionWithPlayer()
{
	if (nullptr == PlayerBase::MainPlayer)
		return;
	
	GameEngineCollision* CollisionPtr = GetBoss()->GetCollision();
	if (false == CollisionPtr->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player) }))
		return;

	PlayerBase::MainPlayer->AttackPlayer();
}


int BossStateBase::CheckCollisionWithNatureMissle()
{
	static std::vector<GameEngineCollision*> NatureMissles;
	GameEngineCollision* CollisionPtr = GetBoss()->GetCollision();
	if (false == CollisionPtr->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::NatureMissle) }, NatureMissles))
		return 0;

	for (GameEngineCollision* NatureCollision : NatureMissles)
	{
		NatureMissleBase* Nature = dynamic_cast<NatureMissleBase*>(NatureCollision->GetActor());
		if (nullptr == Nature)
		{
			MsgAssert("CollisionOrder::NatureMissle에 NatureMissleBase를 상속받지 않은 엑터가 존재합니다");
			return 0;
		}

		Nature->DestroyByBoss();
	}

	return static_cast<int>(NatureMissles.size());
}

