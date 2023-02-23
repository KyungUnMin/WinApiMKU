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

	//�� �÷��̾ ����� �浹�ߴٸ� �浹�� ������� ��������
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
	//�÷��̾�� �浹�� ������ ť�� ��´�
	std::queue<BubbleMissle*> BubbleQ;
	BubbleQ.push(Bubble);
	Fsm->ChangeState(BubbleStateType::Pop);

	//���� ������ �����ϴ� ������� ��� ������
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
				MsgAssert("UpdateOrder::Player_Missle�� BubbleMissle�� �ƴ� ��ü�� �����մϴ�");
				return;
			}

			//Idle������ ����� Move������ ���� �����Ͷ߸��� ó��
			BubbleMissleFSM* NextFSM = NextBubble->GetFSM();
			if (BubbleStateType::Idle != NextFSM->GetCurStateType()
				&& BubbleStateType::Move != NextFSM->GetCurStateType())
			{
				continue;
			}

			//��� ť���� Pop�� ������ ��ġ, ���� Ȯ���� ������ ��ġ, �������� ����
			float4 NowPos = NowBubble->GetPos();
			float4 NextPos = NextBubble->GetPos();
			float4 BubbleColScale = BubbleMissle::CollisionScale * 1.5f;

			//�浹 �� ��ü�鸸
			if (false == GameEngineCollision::CollisionCircleToCircle({ NowPos, BubbleColScale }, { NextPos, BubbleColScale }))
				continue;

			NextFSM->ChangeState(BubbleStateType::Pop);
			BubbleQ.push(NextBubble);
		}
	}

}
