#include "BubbleSpawner.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "PlayerBase.h"
#include "ContentsDefine.h"
#include "ContentsEnum.h"
#include "BubbleMissle.h"
#include "RoundLevelBase.h"
#include "BubbleCore.h"

const float4 BubbleSpawner::SpawnOffset = float4{ 0.f, -30.f };

BubbleSpawner::BubbleSpawner()
{
	
}

BubbleSpawner::~BubbleSpawner()
{
	
}

void BubbleSpawner::Start()
{
	RoundLevel = dynamic_cast<RoundLevelBase*>(GetLevel());
	if (nullptr == RoundLevel)
	{
		MsgAssert("이 버블 스포너는 RoundLevelBase 를 상속받지 않은 Level에서 생성되었습니다");
		return;
	}
}

void BubbleSpawner::Update(float _DeltaTime)
{
	if (nullptr == Player)
		return;

	SetPos(Player->GetPos());
}

void BubbleSpawner::Render(float _DeltaTime)
{
	if (false == BubbleCore::GetInst().IsDebug())
		return;

	//디버그 그리기
}

void BubbleSpawner::CreateBubble(const float4 _Dir)
{
	BubbleMissle* Bubble = GetLevel()->CreateActor<BubbleMissle>(UpdateOrder::Player_Missle);

	float4 CreatePos = GetPos();
	if (nullptr != Player)
	{
		float4 Dir = Player->GetDirVec();
		float4 PlayerCollisionScale = PlayerBase::CollisionScale;
		float4 BubbleCollisionScale = BubbleMissle::CollisionScale;
		CreatePos += Dir * (PlayerCollisionScale.half() + BubbleCollisionScale.half()) + SpawnOffset;
	}

	//Bubble->SetPos(PlayerPos + Dir * (PlayerCollisionScale.half() + BubbleCollisionScale.half()) + SpawnOffset);
	Bubble->SetPos(CreatePos);
	Bubble->Spawner = this;
	Bubble->RoundLevel = RoundLevel;
	Bubble->SetDir(Player->GetDirVec());
	Bubble->Init(Player->GetCharacterType(), Type);
}
