#include "BubbleMissleStateBase.h"
#include <queue>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "BubbleMissle.h"
#include "PlayerBase.h"
#include "BubbleMissleFSM.h"
#include "MonsterBase.h"
#include "PlayerFSM.h"

BubbleMissleStateBase::BubbleMissleStateBase()
{

}

BubbleMissleStateBase::~BubbleMissleStateBase()
{

}

void BubbleMissleStateBase::EnterState()
{
	GameEngineRender* Render = Bubble->GetRender();
	Render->ChangeAnimation(AniName);
}

void BubbleMissleStateBase::PlayerCollisionCheck()
{
	PlayerBase* Player = PlayerBase::MainPlayer;

	if (nullptr == Player)
		return;

	PlayerStateType PlayerState = Player->GetFSM()->GetCurStateByEnum();
	if (PlayerStateType::Damaged == PlayerState)
		return;

	//이 플레이어가 버블과 충돌했다면 충돌한 버블들을 가져오기
	/*float4 PlayerPos = Player->GetPos() + PlayerBase::CollisionOffset;
	float4 PlayerCollisionScale = PlayerBase::CollisionScale;
	
	float4 BubblePos = Bubble->GetPos();
	float4 BubbleCollisionScale = BubbleMissle::CollisionScale;

	if (false == GameEngineCollision::CollisionCircleToCircle(CollisionData{ PlayerPos , PlayerCollisionScale }, CollisionData{ BubblePos, BubbleCollisionScale }))
		return;*/

	if (false == GetBubble()->GetCollisionPtr()->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player) }))
		return;
	
	BubbleChainPop();
}

void BubbleMissleStateBase::DragMonster()
{
	MonsterBase* Monster = GetBubble()->GetCatchTarget();
	if (nullptr == Monster)
		return;

	Monster->SetPos(GetBubble()->GetPos());
}

void BubbleMissleStateBase::BubbleChainPop()
{
	//플레이어와 충돌한 버블을 큐에 담는다
	std::queue<BubbleMissle*> BubbleQ;
	BubbleQ.push(Bubble);
	Fsm->ChangeState(BubbleStateType::Pop);

	//현재 레벨에 존재하는 버블들을 모두 가져옴
	auto Bubbles = Bubble->GetLevel()->GetActors(static_cast<int>(UpdateOrder::Player_Missle));
	while (BubbleQ.size())
	{
		BubbleMissle* NowBubble = BubbleQ.front();
		BubbleQ.pop();

		for (GameEngineActor* BubbleActor : Bubbles)
		{
			BubbleMissle* NextBubble = dynamic_cast<BubbleMissle*>(BubbleActor);
			if (nullptr == NextBubble)
			{
				MsgAssert("UpdateOrder::Player_Missle에 BubbleMissle이 아닌 객체가 존재합니다");
				return;
			}

			//Idle상태의 버블과 Move상태의 버블만 연쇄터뜨리기 처리
			BubbleMissleFSM* NextFSM = NextBubble->GetFSM();
			if (BubbleStateType::Idle != NextFSM->GetCurStateType()
				&& BubbleStateType::Move != NextFSM->GetCurStateType())
			{
				continue;
			}

			//방금 큐에서 Pop된 버블의 위치, 지금 확인할 버블의 위치, 연쇄터짐 범위
			float4 NowPos = NowBubble->GetPos();
			float4 NextPos = NextBubble->GetPos();
			float4 BubbleColScale = BubbleMissle::CollisionScale * 1.5f;

			//충돌 한 물체들만
			if (false == GameEngineCollision::CollisionCircleToCircle({ NowPos, BubbleColScale }, { NextPos, BubbleColScale }))
				continue;

			NextFSM->ChangeState(BubbleStateType::Pop);
			BubbleQ.push(NextBubble);
		}
	}

}
