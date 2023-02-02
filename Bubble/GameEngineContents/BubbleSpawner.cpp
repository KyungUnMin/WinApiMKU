#include "BubbleSpawner.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "PlayerBase.h"
#include "ContentsDefine.h"
#include "ContentsEnum.h"
#include "BubbleMissle_Normal.h"

std::vector<BubbleMissleBase*>	BubbleSpawner::Bubbles;

//레벨이 전환될때 호출할 예정
void BubbleSpawner::AllDeath()
{
	for (size_t i = 0; i < Bubbles.size(); ++i)
	{
		//그러니 버블을 사용할땐 절때 미리 Death시키면 안된다
		//미리 Death시키면 이 포인터는 댕글링 포인터가 된다
		Bubbles[i]->Death();
	}

	Bubbles.clear();
}

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
}

void BubbleSpawner::Update(float _DeltaTime)
{
	if (false == GameEngineInput::IsDown(PLAYER_ATTACK))
		return;

	//생성한 버블은 static 벡터에 보관된다
	BubbleMissleBase* BubblePtr = CreateBubble();

	float4 PlayerPos = Player->GetPos();
	float4 PlayerDir = Player->GetDirVec();

	//일단은 임시로 이렇게 하고 나중에 버블의 Collision 반지름 + 플레이어 반지름 만큼 이동시키자
	BubblePtr->SetPos(PlayerPos + PlayerDir * 50.f + float4::Up * 30.f);
	BubblePtr->SetDir(Player->GetDirVec());
	BubblePtr->CreateAnimation(Player->GetCharacterType());
}



BubbleMissleBase* BubbleSpawner::CreateBubble()
{
	GameEngineLevel* Level = Player->GetLevel();
	BubbleMissleBase* BubblePtr = nullptr;

	switch (Type)
	{
	case BubbleMissleType::Normal:
		BubblePtr = Level->CreateActor<BubbleMissle_Normal>();
		break;
	case BubbleMissleType::Fire:
		break;
	case BubbleMissleType::Water:
		break;
	case BubbleMissleType::Electronic:
		break;
	case BubbleMissleType::Rainbow:
		break;
	case BubbleMissleType::Windy:
		break;
	case BubbleMissleType::Melody:
		break;
	default:
		break;
	}

	Bubbles.push_back(BubblePtr);
	return BubblePtr;
}
