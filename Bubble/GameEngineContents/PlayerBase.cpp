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

PlayerBase* PlayerBase::MainPlayer = nullptr;

PlayerBase::PlayerBase()
{
	FSMPtr = new PlayerFSM;

	if (this != MainPlayer)
	{
		MainPlayer = this;
	}
}

//플레이어가 들고 있던 컴포넌트들을 delete
PlayerBase::~PlayerBase()
{
	if (nullptr != FSMPtr)
	{
		delete FSMPtr;
		FSMPtr = nullptr;
	}

	if (this == MainPlayer)
	{
		MainPlayer = nullptr;
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
	AliveLiveTime += _DeltaTime;

	//이 객체의 방향을 체크
	MovableActor::Update(_DeltaTime);

	FSMPtr->Update(_DeltaTime);

	if (GameEngineInput::IsDown(PLAYER_ATTACK))
	{
		BBSpawner->CreateBubble(GetDirVec());
	}

	//BubbleCollisionCheck();
	MonsterCollisionCheck();
}

void PlayerBase::Render(float _DeltaTime)
{
	FSMPtr->DebugRender();	
}



//얘도 FSM 안에 넣을까? 그게 좋아 보인다
void PlayerBase::MonsterCollisionCheck()
{
	if (false == CollisionPtr->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Monster) }))
		return;

	if (AliveLiveTime < ProtectionTime)
		return;

	FSMPtr->ChangeState(PlayerStateType::Damaged);
	--lifeCnt;
	AliveLiveTime = 0.f;
}



void PlayerBase::ProtectionRender()
{
	if (ProtectionTime < AliveLiveTime)
	{
		return;
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

