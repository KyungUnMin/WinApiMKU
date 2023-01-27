#include "PlayerState_Idle.h"
#include <vector>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsDefine.h"
#include "ContentsEnum.h"
#include "PlayerState.h"
#include "PlayerBase.h"
#include "RoundLevelBase.h"


PlayerState_Idle::PlayerState_Idle()
{

}

PlayerState_Idle::~PlayerState_Idle()
{

}


void PlayerState_Idle::Start(PlayerCharacterType _CharacterType)
{
	static bool IsLoad = false;
	if (false== IsLoad)
	{
		ResourceLoad("Left_PlayerIdle.bmp", 3, 4);
		ResourceLoad("Right_PlayerIdle.bmp", 3, 4);
		IsLoad = true;
	}

	InitState("Idle");

	int AniIndex = static_cast<int>(_CharacterType) * 3;

	GetRender()->CreateAnimation
	({
		.AnimationName = "Left_Idle",
		.ImageName = "Left_PlayerIdle.bmp",
		.Start = AniIndex,
		.End = AniIndex + 1,
		.InterTimer = 0.25f,
	});

	GetRender()->CreateAnimation
	({
		.AnimationName = "Right_Idle",
		.ImageName = "Right_PlayerIdle.bmp",
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


void PlayerState_Idle::Update(float _DeltaTime)
{
	PlayerStateBase::Update(_DeltaTime);

	//공중에 있는 경우
	if (false == RoundLevel->IsBlockPos(GetPlayer()->GetPos() + float4::Down))
	{
		GetOwner()->ChangeState(PlayerStateType::Falling);
		return;
	}

	//점프하는 경우
	if (true == GameEngineInput::IsDown(PlayerJump))
	{
		GetOwner()->ChangeState(PlayerStateType::Jump);
		return;
	}

	//움직인 경우
	if(GameEngineInput::IsPress(PlayerLeft) || GameEngineInput::IsPress(PlayerRight))
	{
		GetOwner()->ChangeState(PlayerStateType::Move);
		return;
	}
	
}

