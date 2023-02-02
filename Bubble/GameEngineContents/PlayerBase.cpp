#include "PlayerBase.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsDefine.h"
#include "PlayerState.h"
#include "Gravity.h"

const float4 PlayerBase::CollisionScale = float4{ 50.f, 50.f };
const float4 PlayerBase::CollisionOffset = float4{0.f, -30.f};
int PlayerBase::TestCnt = 0;

PlayerBase::PlayerBase()
{
	
}

//�÷��̾ ��� �ִ� ������Ʈ���� delete
PlayerBase::~PlayerBase()
{
	for (auto Pair : Components)
	{
		if (nullptr != Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	}

	Components.clear();
}



void PlayerBase::Start()
{
	CollisionPtr = CreateCollision(CollisionOrder::Player);
	CollisionPtr->SetScale(CollisionScale);
	CollisionPtr->SetPosition(CollisionOffset);

	//�÷��̾ ����� ������Ʈ ����
	Components[ComponentType::PlayerState] = new PlayerState;
	Components[ComponentType::Gravity] = new Gravity;


	//�÷��̾��� ������Ʈ�� �ʱ�ȭ
	for (auto Pair : Components)
	{
		//������Ʈ�� �����ڴ� this
		Pair.second->SetOwner(this);
		Pair.second->Start();
	}
}


void PlayerBase::Update(float _DeltaTime)
{
	//�� ��ü�� ������ üũ
	MovableActor::Update(_DeltaTime);

	//������Ʈ�� Update�� �۵�
	for (auto Pair : Components)
	{
		Pair.second->Update(_DeltaTime);
	}
}
