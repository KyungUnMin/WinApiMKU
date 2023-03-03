#include "BubbleSpawner.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>
#include "PlayerBase.h"
#include "ContentsDefine.h"
#include "ContentsEnum.h"
#include "BubbleMissle.h"
#include "RoundLevelBase.h"
#include "BubbleMissleFSM.h"

const float4 BubbleSpawner::SpawnOffset = float4{ 0.f, -30.f };

BubbleSpawner::BubbleSpawner()
{
	
}

BubbleSpawner::~BubbleSpawner()
{
	
}

void BubbleSpawner::Start()
{
	LoadSFX();
	RoundLevel = dynamic_cast<RoundLevelBase*>(GetLevel());
	if (nullptr == RoundLevel)
	{
		MsgAssert("이 버블 스포너는 RoundLevelBase 를 상속받지 않은 Level에서 생성되었습니다");
		return;
	}
}


void BubbleSpawner::LoadSFX()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");
	Dir.Move("SFX");
	Dir.Move("Bubble");
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("BubbleThrow.wav"));
	IsLoad = true;
}









void BubbleSpawner::Update(float _DeltaTime)
{
	if (nullptr == Player)
		return;

	SetPos(Player->GetPos());
}



void BubbleSpawner::CreateBubble()
{
	//Stage가 전환중일땐 버블을 시키지 않는다
	if (RoundLevel->IsMoving())
		return;

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

	//이것도 나중에 오버로딩하자(플레이어와 기본 스포너 분리)
	if (nullptr != Player)
	{
		Bubble->SetDir(Player->GetDirVec());
		Bubble->Init(Player->GetCharacterType(), Type);
		Bubble->SetMoveSpeed(Player->GetCharacterType());
		GameEngineResources::GetInst().SoundPlay("BubbleThrow.wav");
		return;
	}

	PlayerCharacterType InitColor = static_cast<PlayerCharacterType>(Color);
	if(PlayerCharacterType::COUNT == InitColor)
	{
		int RandNum = rand() % static_cast<int>(PlayerCharacterType::COUNT);
		InitColor = static_cast<PlayerCharacterType>(RandNum);
	}

	Bubble->Init(InitColor, Type);
	Bubble->FSM->ChangeState(BubbleStateType::Move);
}

