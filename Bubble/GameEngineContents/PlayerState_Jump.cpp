#include "PlayerState_Jump.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerState.h"
#include "PlayerBase.h"
#include "RoundLevelBase.h"
#include "ContentsDefine.h"

PlayerState_Jump::PlayerState_Jump()
{

}

PlayerState_Jump::~PlayerState_Jump()
{

}

void PlayerState_Jump::Start(PlayerCharacterType _CharacterType)
{
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad("Left_PlayerJump.bmp", 4, 4);
		ResourceLoad("Right_PlayerJump.bmp", 4, 4);
		IsLoad = true;
	}

	InitState("Jump");

	int AniIndex = static_cast<int>(_CharacterType) * 4;

	GetRender()->CreateAnimation
	({
		.AnimationName = "Left_Jump",
		.ImageName = "Left_PlayerJump.bmp",
		.Start = AniIndex,
		.End = AniIndex + 3,
		.InterTimer = 0.1f,
		.Loop = false
	});

	GetRender()->CreateAnimation
	({
		.AnimationName = "Right_Jump",
		.ImageName = "Right_PlayerJump.bmp",
		.Start = AniIndex,
		.End = AniIndex + 3,
		.InterTimer = 0.1f,
		.Loop = false
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

void PlayerState_Jump::Update(float _DeltaTime)
{
	PlayerStateBase::Update(_DeltaTime);

	if (0.f <= GetPlayer()->GetGravityAcc())
	{
		GetOwner()->ChangeState(PlayerStateType::Falling);
		return;
	}

	if (GameEngineInput::IsPress(PlayerRight) || GameEngineInput::IsPress(PlayerLeft))
	{
		float4 NowPos = GetPlayer()->GetPos();
		float4 MoveDir = GetPlayer()->GetDirVec();

		if (false == RoundLevel->IsBlockPos(NowPos + MoveDir * MovableActor::ColliderRange))
		{
			GetPlayer()->SetMove(MoveDir * AirMoveSpeed * _DeltaTime);
		}
	}
	
}

void PlayerState_Jump::EnterState()
{
	PlayerStateBase::EnterState();
	GetPlayer()->SetMove(float4::Up);
	GetPlayer()->SetGravityAcc(-JumpAcc);
}
