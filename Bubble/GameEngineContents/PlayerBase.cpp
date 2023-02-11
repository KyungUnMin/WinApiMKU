#include "PlayerBase.h"
#include <queue>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsDefine.h"
#include "PlayerFSM.h"
#include "Gravity.h"
#include "BubbleSpawner.h"
#include "BubbleMissle.h"
#include "BubbleMissleFSM.h"

const float4 PlayerBase::CollisionOffset = float4{0.f, -30.f};
const float4 PlayerBase::CollisionScale = float4{ 50.f, 50.f };

PlayerBase::PlayerBase()
{
	FSMPtr = new PlayerFSM;
}

//플레이어가 들고 있던 컴포넌트들을 delete
PlayerBase::~PlayerBase()
{
	if (nullptr != FSMPtr)
	{
		delete FSMPtr;
		FSMPtr = nullptr;
	}
}









void PlayerBase::Start()
{
	MovableActor::Start();

	CollisionPtr = CreateCollision(CollisionOrder::Player);
	CollisionPtr->SetScale(CollisionScale);
	CollisionPtr->SetPosition(CollisionOffset);


	FSMPtr->Player = this;
	FSMPtr->Start();


	BBSpawner = GetLevel()->CreateActor<BubbleSpawner>();
	BBSpawner->SetPlayer(this);
}



void PlayerBase::Update(float _DeltaTime)
{
	//이 객체의 방향을 체크
	MovableActor::Update(_DeltaTime);

	FSMPtr->Update(_DeltaTime);

	/*if (GameEngineInput::IsDown(PLAYER_ATTACK))
	{
		FsmPtr->PlayerAttack();
		BBSpawner->CreateBubble(GetDirVec());
	}*/

	//BubbleCollisionCheck();
}

void PlayerBase::Render(float _DeltaTime)
{
	MovableActor::Render(_DeltaTime);
	FSMPtr->DebugRender();	
}







//플레이어와 버블의 충돌 처리및 버블 연쇄적으로 터뜨리기
void PlayerBase::BubbleCollisionCheck()
{
	//이 플레이어가 버블과 충돌했다면 충돌한 버블들을 가져오기
	std::vector<GameEngineCollision*> BubbleCollision;
	if (false == CollisionPtr->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player_Missle) }, BubbleCollision))
		return;

	//플레이어와 충돌한 버블을 큐에 담는다
	std::queue<BubbleMissle*> BubbleQ;
	for (GameEngineCollision* BubbleCol : BubbleCollision)
	{
		BubbleMissle* Bubble = dynamic_cast<BubbleMissle*>(BubbleCol->GetActor());
		if (nullptr == Bubble)
		{
			MsgAssert("UpdateOrder::Player_Missle에 BubbleMissle이 아닌 객체가 존재합니다");
			return;
		}

		//플레이어와 충돌한 버블을 pop처리
		Bubble->GetFSM()->ChangeState(BubbleStateType::Pop);

		//버블의 연쇄Pop을 위해 큐에 담는다
		BubbleQ.push(Bubble);
	}

	//현재 레벨에 존재하는 버블들을 모두 가져옴
	auto Bubbles = GetLevel()->GetActors(static_cast<int>(UpdateOrder::Player_Missle));
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







PlayerCharacterType PlayerBase::GetCharacterType()
{
	if (CharcterType == PlayerCharacterType::COUNT)
	{
		MsgAssert("플레이어 타입을 설정해주지 않았습니다");
		return PlayerCharacterType::COUNT;
	}

	return CharcterType;
}

