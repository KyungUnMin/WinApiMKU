#include "PlayerState_Move.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerBase.h"
#include "ContentsDefine.h"
#include "PlayerState.h"
#include "RoundLevelBase.h"

PlayerState_Move::PlayerState_Move()
{

}

PlayerState_Move::~PlayerState_Move()
{

}

void PlayerState_Move::Start(PlayerCharacterType _CharacterType)
{
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad("Left_PlayerMove.bmp", 5, 4);
		ResourceLoad("Right_PlayerMove.bmp", 5, 4);
		IsLoad = true;
	}

	InitState("Move");

	int AniIndex = static_cast<int>(_CharacterType) * 5;

	GetRender()->CreateAnimation
	({
		.AnimationName = "Left_Move",
		.ImageName = "Left_PlayerMove.bmp",
		.Start = AniIndex,
		.End = AniIndex + 4,
		.InterTimer = 0.1f,
	});

	GetRender()->CreateAnimation
	({
		.AnimationName = "Right_Move",
		.ImageName = "Right_PlayerMove.bmp",
		.Start = AniIndex,
		.End = AniIndex + 4,
		.InterTimer = 0.1f,
	});

	const std::string StartDir = GetPlayer()->GetDirStr();
	GetRender()->ChangeAnimation(StartDir + "Move");
	GetRender()->Off();



	RoundLevel = dynamic_cast<RoundLevelBase*>(GetPlayer()->GetLevel());
	if (nullptr == RoundLevel)
	{
		MsgAssert("RoundLevel이 현재 레벨과 연결되어 있지 않습니다");
	}
}


void PlayerState_Move::Update(float _DeltaTime)
{
	if (true == GetPlayer()->IsDirChanged())
	{
		const std::string NowDir = GetPlayer()->GetDirStr();
		GetRender()->ChangeAnimation(NowDir + "Move");
	}

	if (GameEngineInput::IsUp(PlayerLeft) || GameEngineInput::IsUp(PlayerRight))
	{
		GetOwner()->ChangeState(PlayerStateType::Idle);
		return;
	}

	float4 NowPos = GetPlayer()->GetPos();
	float4 MoveDir = GetPlayer()->GetDirVec();

	if (true == RoundLevel->IsBlockPos(NowPos + MoveDir * ColliderScale))
		return;

	if (true == RoundLevel->IsBlockPos(NowPos + float4::Down))
	{
		GetPlayer()->SetMove(MoveDir * MoveSpeed * _DeltaTime);
	}
	else
	{
		GetPlayer()->SetMove(MoveDir * AirMoveSpeed * _DeltaTime);
	}
}

