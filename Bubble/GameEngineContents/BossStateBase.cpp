#include "BossStateBase.h"
#include <string>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "BossMonsterFSM.h"
#include "BossMonster.h"

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

bool BossStateBase::IsCollision(CollisionOrder _TargetGroup)
{
	GameEngineCollision* CollisionPtr = GetBoss()->GetCollision();
	return CollisionPtr->Collision({ .TargetGroup = static_cast<int>(_TargetGroup) });
}