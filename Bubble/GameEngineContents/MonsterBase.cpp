#include "MonsterBase.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include "MonsterFSM.h"
#include "PlayerBase.h"
#include "BubbleMissle.h"

const float4 MonsterBase::RenderScale		= float4{ 200.f, 200.f };
const float4 MonsterBase::CollisionScale		= float4{ 50.f, 50.f };
const float4 MonsterBase::CollisionOffset	= float4{ 0.f, -30.f };

MonsterBase::MonsterBase()
{
	FsmPtr = new MonsterFSM;
	FsmPtr->SetMonser(this);
}

MonsterBase::~MonsterBase()
{
	if (nullptr != FsmPtr)
	{
		delete FsmPtr;
		FsmPtr = nullptr;
	}
}


void MonsterBase::Start()
{
	MovableActor::Start();
	RenderPtr = CreateRender(RenderOrder::Monster1);
	RenderPtr->SetScale(RenderScale);

	CollisionPtr = CreateCollision(CollisionOrder::Monster);
	CollisionPtr->SetScale(CollisionScale);
	CollisionPtr->SetPosition(CollisionOffset);
}

void MonsterBase::Start_FSM(MonsterStateType _StartType)
{
	if (true == FsmPtr->States.empty())
	{
		MsgAssert("���� ������ FSM�� ��������� �ʾҽ��ϴ�");
		return;
	}

	FsmPtr->Start();
	FsmPtr->ChangeState(_StartType);
}



void MonsterBase::Update(float _DeltaTime)
{
	FsmPtr->Update(_DeltaTime);
}

void MonsterBase::Render(float _DeltaTime)
{
	FsmPtr->Render(_DeltaTime);
}



void MonsterBase::AttackedBubble(BubbleMissle* _LockedBubble)
{
	LockedBubble = _LockedBubble;
	FsmPtr->ChangeState(MonsterStateType::Lock);
}

bool MonsterBase::IsLocked()
{
	if (MonsterStateType::Lock == FsmPtr->GetCurStateByEnum())
		return true;

	if (MonsterStateType::Dead == FsmPtr->GetCurStateByEnum())
		return true;

	return false;
}

void MonsterBase::DeathFromBubble()
{
	if (false == IsLocked())
	{
		MsgAssert("�� �Լ��� ���Ͱ� Bubble�� ������������ ����� �� �ֽ��ϴ�");
		return;
	}

	FsmPtr->ChangeState(MonsterStateType::Dead);
}

void MonsterBase::DeathFromNature(NatureMissleBase* _Nature)
{
	if (_Nature == nullptr)
	{
		MsgAssert("NatureMissle Ŭ������ �� �Լ��� ȣ���� �� �ֽ��ϴ�");
		return;
	}

	FsmPtr->ChangeState(MonsterStateType::Dead);
}

void MonsterBase::FSMReset()
{
	MonsterStateType NowState = FsmPtr->GetCurStateByEnum();

	if (MonsterStateType::Falling == NowState)
		return;

	if (nullptr != LockedBubble)
	{
		LockedBubble->SetCatchTarget(nullptr);
		LockedBubble = nullptr;
	}

	FsmPtr->ChangeState(MonsterStateType::Falling);
}