#include "BubbleSpawner.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "PlayerBase.h"
#include "ContentsDefine.h"
#include "ContentsEnum.h"
#include "BubbleMissle.h"
#include "RoundLevelBase.h"

const float4 BubbleSpawner::SpawnOffset = float4{ 0.f, -30.f };

BubbleSpawner::BubbleSpawner()
{

}

BubbleSpawner::~BubbleSpawner()
{
	
}

void BubbleSpawner::Start()
{
	Player = dynamic_cast<PlayerBase*>(GetOwner());
	if (nullptr == Player)
	{
		MsgAssert("BubbleSpawner의 주인 클래스는 PlayerBase를 상속받지 않았습니다");
		return;
	}

	RoundLevel = dynamic_cast<RoundLevelBase*>(Player->GetLevel());
	if (nullptr == RoundLevel)
	{
		MsgAssert("이 버블 스포너는 RoundLevelBase 를 상속받지 않은 Level에서 생성되었습니다");
		return;
	}
}

void BubbleSpawner::Update(float _DeltaTime)
{
	//플레이어와 버블 충돌 체크


	if (true == GameEngineInput::IsDown(PLAYER_ATTACK))
	{
		CreateBubble();
	}
}

void BubbleSpawner::CreateBubble()
{
	BubbleMissle* Bubble = Player->GetLevel()->CreateActor<BubbleMissle>(UpdateOrder::Player_Missle);

	float4 PlayerPos = Player->GetPos();
	float4 Dir = Player->GetDirVec();

	float4 PlayerCollisionScale = PlayerBase::CollisionScale;
	float4 BubbleCollisionScale = BubbleMissle::CollisionScale;

	Bubble->SetPos(PlayerPos + Dir * (PlayerCollisionScale.half() + BubbleCollisionScale.half()) + SpawnOffset);
	Bubble->Spawner = this;
	Bubble->RoundLevel = RoundLevel;
	Bubble->SetDir(Player->GetDirVec());
	Bubble->Init(Player->GetCharacterType(), Type);
}
