#include "PlayerState_Idle.h"
#include <vector>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"
#include "PlayerState.h"
#include "PlayerBase.h"

PlayerState_Idle::PlayerState_Idle()
{

}

PlayerState_Idle::~PlayerState_Idle()
{

}


void PlayerState_Idle::Init(PlayerCharacterType _CharacterType)
{
	static bool IsInit = false;
	if (false== IsInit)
	{
		ResourceLoad("Left_PlayerIdle.bmp", 3, 4);
		ResourceLoad("Right_PlayerIdle.bmp", 3, 4);
		IsInit = true;
	}

	PlayerRender = GetPlayer()->CreateRender(RoundRenderOrder::Player1);
	PlayerRender->SetScale(PlayerStateBase::PlayerScale);

	int AniIndex = static_cast<int>(_CharacterType) * 3;

	PlayerRender->CreateAnimation
	({
		.AnimationName = "Left_Idle",
		.ImageName = "Left_PlayerIdle.bmp",
		.Start = AniIndex,
		.End = AniIndex + 1,
		.InterTimer = 0.25f,
	});

	PlayerRender->CreateAnimation
	({
		.AnimationName = "Right_Idle",
		.ImageName = "Right_PlayerIdle.bmp",
		.Start = AniIndex,
		.End = AniIndex + 1,
		.InterTimer = 0.25f,
	});

	const std::string StartDir = GetPlayer()->GetDirStr();
	PlayerRender->ChangeAnimation(StartDir + "Idle");
	PlayerRender->Off();
}

void PlayerState_Idle::EnterState()
{
	const std::string StartDir = GetPlayer()->GetDirStr();
	PlayerRender->ChangeAnimation(StartDir + "Idle");
	PlayerRender->On();
}

void PlayerState_Idle::Update(float _DeltaTime)
{
	if (true == GetPlayer()->IsDirChanged())
	{
		const std::string NowDir = GetPlayer()->GetDirStr();
		PlayerRender->ChangeAnimation(NowDir + "Idle");
	}

	if(GameEngineInput::IsPress("PlayerLeft") || GameEngineInput::IsPress("PlayerRight"))
	{
		GetOwner()->ChangeState(PlayerStateType::Move);
		return;
	}

}

void PlayerState_Idle::ExitState()
{
	PlayerRender->Off();
}
