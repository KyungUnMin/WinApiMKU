#include "MonsterStateBase.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "MonsterBase.h"
#include "PlayerBase.h"
#include "BubbleMissle.h"

MonsterStateBase::MonsterStateBase()
{
	
}

MonsterStateBase::~MonsterStateBase()
{

}

void MonsterStateBase::Start()
{
	if (nullptr == GetMonster())
	{
		MsgAssert("현재 State에 몬스터를 연결해주지 않았습니다");
		return;
	}

	if (nullptr == GetFSM())
	{
		MsgAssert("현재 State에 FSM을 연결해주지 않았습니다");
		return;
	}
}

void MonsterStateBase::EnterState()
{
	if (true == NowAniName.empty())
	{
		MsgAssert("현재 상태의 애니메이션을 설정해주지 않았습니다");
		return;
	}

	ChangeAniDir();
}

void MonsterStateBase::ChangeAniDir()
{
	const std::string NowDir = Monster->GetDirStr();
	GameEngineRender* RenderPtr = Monster->GetRender();
	RenderPtr->ChangeAnimation(NowDir + NowAniName, true);
}



void MonsterStateBase::CreateAnimation(const FrameAnimationParameter& _Param)
{
	GameEngineRender* RenderPtr = GetMonster()->GetRender();

	if (nullptr == RenderPtr)
	{
		MsgAssert("이 몬스터에는 GameEngineRender를 만들어주지 않았습니다");
		return;
	}

	RenderPtr->CreateAnimation(_Param);
}


float4 MonsterStateBase::GetHorizonDirToPlayer()
{
	float4 PlayerPos = PlayerBase::MainPlayer->GetPos();
	float4 MonsterPos = Monster->GetPos();

	float4 Dir = PlayerPos - MonsterPos;
	Dir.y = 0;
	Dir.Normalize();

	return Dir;
}

bool MonsterStateBase::PlayerCollisionCheck()
{
	if (nullptr == PlayerBase::MainPlayer)
		return false;

	/*float4 PlayerPos = PlayerBase::MainPlayer->GetPos() + PlayerBase::CollisionOffset;
	float4 PlayerCollisionScale = PlayerBase::CollisionScale;
	float4 MonsterPos = GetMonster()->GetPos() + MonsterBase::CollisionOffset;
	float4 BubbleCollisionScale = BubbleMissle::CollisionScale;*/


	return GetMonster()->GetCollision()->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player) });
	//return GameEngineCollision::CollisionCircleToCircle({ PlayerPos, PlayerCollisionScale }, { MonsterPos , BubbleCollisionScale });
}

