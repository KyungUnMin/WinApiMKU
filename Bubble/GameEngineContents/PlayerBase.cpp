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
#include "NatureMissle_Fire.h"
#include "GhostTracer.h"

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

//플레이어가 들고 있던 컴포넌트들을 delete
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

	//이 객체의 방향을 체크
	MovableActor::Update(_DeltaTime);

	CheckStandOnStage();
	FSMPtr->Update(_DeltaTime);

	//부활한 뒤 무적 연출
	ProtectionRender();

	if ((GhostSpawnTime < AliveLiveTime) && (nullptr == GhostTracer::MainGhost))
	{
		GetLevel()->CreateActor<GhostTracer>(UpdateOrder::BossMonster);
	}
}

void PlayerBase::CheckStandOnStage()
{
	float4 NowPos = GetPos();
	if (0.f < NowPos.y)
		return;

	FSMPtr->ChangeState(PlayerStateType::Falling);
	SetPos(NowPos * float4::Right);
}


void PlayerBase::Render(float _DeltaTime)
{
	FSMPtr->DebugRender();	
}




//몬스터쪽에서 호출됨
void PlayerBase::AttackPlayer()
{
	//무적모드일때는 공격 취소
	if (true == Unbeatable)
		return;

	//무적 시간
	if (AliveLiveTime < ProtectionTime)
		return;

	if (PlayerStateType::Damaged == FSMPtr->GetCurStateByEnum())
		return;

	if (PlayerStateType::EnterDoor	== FSMPtr->GetCurStateByEnum())
		return;

	if (nullptr != GhostTracer::MainGhost)
	{
		GhostTracer::MainGhost->KillPlayer();
	}

	//좋은 방법은 아니여도 간단하게 이렇게만 하자
	NatureMissle_Fire::BurnTimeReset();

	--lifeCnt;

	//여기서도 호출되고
	ResetAliveTime();

	//Damaged가 끝날때도 호출된다(의도하진 않은 거지만 일단 두자)
	FSMPtr->ChangeState(PlayerStateType::Damaged);
}



void PlayerBase::ProtectionRender()
{
	//레벨이 시작하면서도 동작하기 때문에 초반엔 ProtectionTime 시간만큼 무적
	RenderPtr->SetAlpha(RenderAlpha);
	if (ProtectionTime < AliveLiveTime)
	{
		RenderAlpha = 255;
		return;
	}

	PlayerStateType PlayerCurState = FSMPtr->GetCurStateByEnum();

	if (PlayerStateType::Damaged == PlayerCurState)
		return;

	if (PlayerStateType::StageMove == PlayerCurState)
		return;

	if (PlayerStateType::Embarrassed == PlayerCurState)
		return;

	if (PlayerStateType::EnterDoor == PlayerCurState)
		return;

	//RenderPtr->OnOffSwtich();
	RenderAlpha = (255 == RenderAlpha) ? 100 : 255;
}






PlayerCharacterType PlayerBase::GetCharacterType()
{
	if (CharcterType == PlayerCharacterType::COUNT)
	{
		MsgAssert("플레이어 타입을 설정해주지 않았습니다");
		return PlayerCharacterType::COUNT;
	}

	return CharcterType;
}

