#include "MonsterMissleBase.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include "PlayerBase.h"

const float4 MonsterMissleBase::RenderScale		= float4{ 150.f, 150.f };
const float4 MonsterMissleBase::CollisionScale	= float4{ 50.f, 50.f };

MonsterMissleBase::MonsterMissleBase()
{

}

MonsterMissleBase::~MonsterMissleBase()
{

}


void MonsterMissleBase::Start()
{
	MovableActor::Start();
	RenderPtr = CreateRender(RenderOrder::Monster1);
	RenderPtr->SetScale(RenderScale);

	CollisionPtr = CreateCollision(CollisionOrder::Monster_Missle);
	CollisionPtr->SetScale(CollisionScale);
}

bool MonsterMissleBase::PlayerCollisionCheck()
{
	if (nullptr == PlayerBase::MainPlayer)
		return false;
	
	float4 PlayerPos = PlayerBase::MainPlayer->GetPos();
	float4 PlayerColScale = PlayerBase::CollisionScale;
	float4 ThisPos = GetPos();
	float4 ThisColScale = CollisionScale;

	if (false == GameEngineCollision::CollisionCircleToCircle({ PlayerPos, PlayerColScale }, { ThisPos, ThisColScale }))
		return false;

	PlayerBase::MainPlayer->AttackPlayer();
	return true;
}
