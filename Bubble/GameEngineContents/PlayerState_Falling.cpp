#include "PlayerState_Falling.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerBase.h"
#include "RoundLevelBase.h"
#include "PlayerState.h"
#include "ContentsDefine.h"

PlayerState_Falling::PlayerState_Falling()
{

}

PlayerState_Falling::~PlayerState_Falling()
{

}

void PlayerState_Falling::Start(PlayerCharacterType _CharacterType)
{
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad("Left_PlayerFalling.bmp", 2, 4);
		ResourceLoad("Right_PlayerFalling.bmp", 2, 4);
		IsLoad = true;
	}

	InitState("Falling");

	int AniIndex = static_cast<int>(_CharacterType) * 2;

	GetRender()->CreateAnimation
	({
		.AnimationName = "Left_Falling",
		.ImageName = "Left_PlayerFalling.bmp",
		.Start = AniIndex,
		.End = AniIndex + 1,
		.InterTimer = 0.25f,
	});

	GetRender()->CreateAnimation
	({
		.AnimationName = "Right_Falling",
		.ImageName = "Right_PlayerFalling.bmp",
		.Start = AniIndex,
		.End = AniIndex + 1,
		.InterTimer = 0.25f,
	});

	const std::string StartDir = GetPlayer()->GetDirStr();
	GetRender()->ChangeAnimation(StartDir + GetAniName());
	GetRender()->Off();

	RoundLevel = dynamic_cast<RoundLevelBase*>(GetPlayer()->GetLevel());
	if (nullptr == RoundLevel)
	{
		MsgAssert("RoundLevel이 현재 레벨과 연결되어 있지 않습니다");
	}
}


void PlayerState_Falling::Update(float _DeltaTime)
{
	PlayerStateBase::Update(_DeltaTime);

	float4 NowPos = GetPlayer()->GetPos();

	float4 MoveDir = GetPlayer()->GetDirVec();
	if (false == RoundLevel->IsBlockPos(NowPos + MoveDir * MovableActor::ColliderRange))
	{
		GetPlayer()->SetMove(MoveDir * AirMoveSpeed * _DeltaTime);
	}

	//공중에 있는 경우
	if (false == RoundLevel->IsBlockPos(NowPos + float4::Down))
		return;

	//점프하는 경우
	if (true == GameEngineInput::IsDown(PlayerJump))
	{
		GetOwner()->ChangeState(PlayerStateType::Jump);
		return;
	}

	//그 외에는 Idle
	GetOwner()->ChangeState(PlayerStateType::Idle);
}
