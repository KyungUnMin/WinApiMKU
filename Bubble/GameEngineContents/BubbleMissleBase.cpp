#include "BubbleMissleBase.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "RoundLevelBase.h"
#include "MonsterBase.h"

const float		BubbleMissleBase::MoveSpeed		= 400.f;
const float		BubbleMissleBase::RaiseSpeed		= 50.f;
const float4	BubbleMissleBase::RenderScale		= float4{ 150.f, 150.f };
const float4	BubbleMissleBase::CollisionScale	= float4{ 50.f, 50.f };

BubbleMissleBase::BubbleMissleBase()
{
	
}

BubbleMissleBase::~BubbleMissleBase()
{

}






//Throw �ִϸ��̼� �̹����� �ε�
void BubbleMissleBase::Start()
{
	//�� Ŭ���� ��Ʋ�� ó������ ���ҽ� �ε��ϱ�
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad("BubbleThrow.bmp", 6, 4);
		IsLoad = true;
	}

	BubbleRender = CreateRender(RoundRenderOrder::AttackBubble);
	BubbleRender->SetScale(RenderScale);
	CollisionPtr = CreateCollision(CollisionOrder::Player_Missle);
	CollisionPtr->SetScale(CollisionScale);

	RoundLevel = dynamic_cast<RoundLevelBase*>(GetLevel());
	if (nullptr == RoundLevel)
	{
		MsgAssert("���� Bubble�� RoundLevelBase�� ��ӹ��� ���� Level���� �����Ǿ����ϴ�");
	}
}

//Throw�ִϸ��̼� �ε�
void BubbleMissleBase::ResourceLoad(const std::string_view& _AniImgPath, int _X, int _Y)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Bubble");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(_AniImgPath))->Cut(_X, _Y);
}


//Throw �ִϸ��̼� ����
void BubbleMissleBase::CreateAnimation(PlayerCharacterType _CharacterType)
{
	int ThrowAniIndex = static_cast<int>(_CharacterType) * 6;

	BubbleRender->CreateAnimation
	({
		.AnimationName = "BubbleThrow",
		.ImageName = "BubbleThrow.bmp",
		.Start = ThrowAniIndex,
		.End = ThrowAniIndex + 4,
		.Loop = false
	});

	BubbleRender->ChangeAnimation("BubbleThrow");

}


void BubbleMissleBase::Update(float _DeltaTime)
{
	switch (State)
	{
	case BubbleState::Throw:
		ThrowUpdate(_DeltaTime);
		break;
	case BubbleState::Idle:
		IdleUpdate(_DeltaTime);
		break;
	case BubbleState::Pop:
		GameEngineObject::Off();
		break;
	}
}



void BubbleMissleBase::ThrowUpdate(float _DeltaTime)
{
	//BubbleThrow�� ����� ��������
	if (true == BubbleRender->IsAnimationEnd())
	{
		State = BubbleState::Idle;
		BubbleRender->ChangeAnimation("BubbleIdle");
		return;
	}
	

	std::vector<GameEngineCollision*> Monsters;
	if (true == CollisionPtr->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Monster) }, Monsters))
	{
		State = BubbleState::Idle;
		//Monsters.front()->GetActor()->Off();
		Monsters.front()->Off();
		BubbleRender->ChangeAnimation("BubbleIdle");

		MonsterBase* Monster = dynamic_cast<MonsterBase*>(Monsters.front()->GetActor());
		if (nullptr == Monster)
		{
			MsgAssert("���Ͱ� �ƴ� ��ü�� ���� �浹 �׷쿡 �����ֽ��ϴ�");
			return;
		}

		Monster->BubbleLock(this);
		LockMonster = Monster;
		return;
	}

	//BubbleThrow�� ������϶� �ʿ� ���������� �ʴٸ� �ش� �������� �����δ�
	float4 NextMove = GetDirVec() * MoveSpeed * _DeltaTime;
	if (true == RoundLevel->IsBlockPos(GetPos() +  NextMove))
		return;

	SetMove(NextMove);
}

void BubbleMissleBase::IdleUpdate(float _DeltaTime)
{
	if (GetPos().y < 100.f)
		return;

	SetMove(float4::Up * RaiseSpeed * _DeltaTime);
}

void BubbleMissleBase::BubblePop()
{
	if (nullptr != LockMonster)
	{
		LockMonster->Off();
	}


	State = BubbleState::Pop;
	GameEngineObject::Off();
}
