#include "PlayerState_Idle.h"
#include <vector>

#include<GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsDefine.h"
#include "ContentsEnum.h"
#include "PlayerFSM.h"
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
	//딱 한번만 리소스 로드
	static bool IsLoad = false;
	if (false== IsLoad)
	{
		ResourceLoad();
		IsLoad = true;
	}

	ConnectRoundLevel();
	CreateAnimation(_CharacterType);
}



void PlayerState_Idle::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Player");
	Dir.Move("Idle");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_PlayerIdle.bmp"))->Cut(2, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_PlayerIdle.bmp"))->Cut(2, 4);
}

void PlayerState_Idle::CreateAnimation(PlayerCharacterType _CharacterType)
{
	int ImgXCnt = 2;
	int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

	SetAniName("Idle");
	std::string LeftAniName = MovableActor::LeftStr + GetAniName();
	std::string RightAniName = MovableActor::RightStr + GetAniName();

	//왼쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = "Left_PlayerIdle.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.25f,
	});

	//오른쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = RightAniName,
		.ImageName = "Right_PlayerIdle.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.25f,
	});
}






void PlayerState_Idle::EnterState()
{
	PlayerStateBase::EnterState();
	AccTime = 0.f;
}



void PlayerState_Idle::Update(float _DeltaTime)
{
	//스테이지가 이동할 때
	if (true == GetRoundLevel()->IsMoving())
	{
		GetFSM()->ChangeState(PlayerStateType::StageMove);
		return;
	}

	//공격키를 누른경우
	if (true == GameEngineInput::IsDown(PLAYER_ATTACK))
	{
		GetFSM()->ChangeState(PlayerStateType::IdleAttack);
		return;
	}

	//허공에 떠있는 경우
	if (false == GetPlayer()->IsGround(PlayerBase::CollisionScale))
	{
		GetFSM()->ChangeState(PlayerStateType::Falling);
		return;
	}

	//점프하는 경우
	if (true == GameEngineInput::IsDown(PLAYER_JUMP))
	{
		GetFSM()->ChangeState(PlayerStateType::Jump);
		return;
	}

	//움직인 경우
	if (GameEngineInput::IsPress(PLAYER_LEFT) || GameEngineInput::IsPress(PLAYER_RIGHT))
	{
		GetFSM()->ChangeState(PlayerStateType::Move);
		return;
	}

	//idle 상태가 된지 SleepChangeTime시간만큼 흘렀을때
	AccTime += _DeltaTime;

	if (SleepChangeTime < AccTime)
	{
		GetFSM()->ChangeState(PlayerStateType::Sleep);
		return;
	}
}