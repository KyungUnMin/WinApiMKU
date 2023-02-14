#include "PlayerBase.h"
#include <queue>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
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

	RenderPtr = CreateRender(RenderOrder::Player1);
	RenderPtr->SetScale(PlayerRenderScale);


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

	//부활한 뒤 무적 연출
	ProtectionRender();
}

void PlayerBase::Render(float _DeltaTime)
{
	FSMPtr->DebugRender();	
}





void PlayerBase::AttackPlayer()
{
	//무적 시간
	if (AliveLiveTime < ProtectionTime)
		return;

	if (PlayerStateType::Damaged == FSMPtr->GetCurStateByEnum())
		return;

	--lifeCnt;
	FSMPtr->ChangeState(PlayerStateType::Damaged);
}



void PlayerBase::ProtectionRender()
{
	//레벨이 시작하면서도 동작하기 때문에 초반엔 ProtectionTime 시간만큼 무적
	if (ProtectionTime < AliveLiveTime)
	{
		RenderPtr->On();
		return;
	}

	RenderPtr->OnOffSwtich();
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

