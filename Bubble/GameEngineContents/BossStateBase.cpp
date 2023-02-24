#include "BossStateBase.h"
#include <string>
#include <GameEngineCore/GameEngineRender.h>
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