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

//������ ��ȯ�ɶ� ȣ���� ����
void BubbleSpawner::AllDeath()
{
	for (size_t i = 0; i < Bubbles.size(); ++i)
	{
		//�׷��� ������ ����Ҷ� ���� �̸� Death��Ű�� �ȵȴ�
		//�̸� Death��Ű�� �� �����ʹ� ��۸� �����Ͱ� �ȴ�
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
		MsgAssert("BubbleSpawner�� ���� Ŭ������ PlayerBase�� ��ӹ��� �ʾҽ��ϴ�");
		return;
	}
}

void BubbleSpawner::Update(float _DeltaTime)
{
	if (false == GameEngineInput::IsDown(PLAYER_ATTACK))
		return;

	//������ ������ static ���Ϳ� �����ȴ�
	BubbleMissleBase* BubblePtr = CreateBubble();

	float4 PlayerPos = Player->GetPos();
	float4 PlayerDir = Player->GetDirVec();

	//�ϴ��� �ӽ÷� �̷��� �ϰ� ���߿� ������ Collision ������ + �÷��̾� ������ ��ŭ �̵���Ű��
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
