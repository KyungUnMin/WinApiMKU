#include "PlayerBase.h"
#include <queue>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>
#include "ContentsDefine.h"
#include "PlayerFSM.h"
#include "Gravity.h"
#include "BubbleSpawner.h"
#include "BubbleMissle.h"
#include "BubbleMissleFSM.h"

const float4	PlayerBase::CollisionOffset = float4{0.f, -30.f};
const float4	PlayerBase::CollisionScale = float4{ 50.f, 50.f };
bool					PlayerBase::Unbeatable = false;

PlayerBase* PlayerBase::MainPlayer = nullptr;

PlayerBase::PlayerBase()
{
	FSMPtr = new PlayerFSM;

	if (this != MainPlayer)
	{
		MainPlayer = this;
	}
}

//�÷��̾ ��� �ִ� ������Ʈ���� delete
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




void PlayerBase::UnbeatableSwitch()
{
	Unbeatable = !Unbeatable;
	if (nullptr == MainPlayer)
		return;

	if (true == Unbeatable)
	{
		MainPlayer->ShieldRender->On();
	}
	else
	{
		MainPlayer->ShieldRender->Off();
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

	CreateCheetShield();
}

void PlayerBase::CreateCheetShield()
{
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Image");
		Dir.Move("Common");
		Dir.Move("Player");
		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("CheetShield.bmp"))->Cut(3, 1);
		IsLoad = true;
	}

	ShieldRender = CreateRender(RenderOrder::Shield);
	ShieldRender->SetScale(PlayerRenderScale);
	ShieldRender->SetPosition(CollisionOffset);
	ShieldRender->SetAlpha(100);

	ShieldRender->CreateAnimation
	({
		.AnimationName = "CheetShield",
		.ImageName = "CheetShield.bmp",
		.Start = 0,
		.End = 2,
		.InterTimer = 0.1f,
		.Loop = true
	});
	
	ShieldRender->ChangeAnimation("CheetShield");

	if (false == Unbeatable)
	{
		ShieldRender->Off();
	}
}


void PlayerBase::Update(float _DeltaTime)
{
	AliveLiveTime += _DeltaTime;

	//�� ��ü�� ������ üũ
	MovableActor::Update(_DeltaTime);

	FSMPtr->Update(_DeltaTime);

	//��Ȱ�� �� ���� ����
	ProtectionRender();
}

void PlayerBase::Render(float _DeltaTime)
{
	FSMPtr->DebugRender();	
}




//�����ʿ��� ȣ���
void PlayerBase::AttackPlayer()
{
	//��������϶��� ���� ���
	if (true == Unbeatable)
		return;

	//���� �ð�
	if (AliveLiveTime < ProtectionTime)
		return;

	if (PlayerStateType::Damaged == FSMPtr->GetCurStateByEnum())
		return;

	if (PlayerStateType::EnterDoor	== FSMPtr->GetCurStateByEnum())
		return;

	--lifeCnt;
	FSMPtr->ChangeState(PlayerStateType::Damaged);
}



void PlayerBase::ProtectionRender()
{
	//������ �����ϸ鼭�� �����ϱ� ������ �ʹݿ� ProtectionTime �ð���ŭ ����
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
		MsgAssert("�÷��̾� Ÿ���� ���������� �ʾҽ��ϴ�");
		return PlayerCharacterType::COUNT;
	}

	return CharcterType;
}

