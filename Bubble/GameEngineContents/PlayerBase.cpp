#include "PlayerBase.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "ContentsDefine.h"
#include "PlayerState.h"
#include "Gravity.h"

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
	//�� �ѹ� �÷��̾ ����� Ű ����
	static bool IsCreatedKey = false;
	if (false == IsCreatedKey)
	{
		IsCreatedKey = true;

		GameEngineInput::CreateKey(PlayerLeft, LeftKey);
		GameEngineInput::CreateKey(PlayerRight, RightKey);
		GameEngineInput::CreateKey(PlayerJump, JumpKey);
		GameEngineInput::CreateKey(PlayerAttack, AttackKey);
	}

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
