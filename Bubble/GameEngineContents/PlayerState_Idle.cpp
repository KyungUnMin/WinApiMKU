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
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_PlayerIdle_Attack.bmp"))->Cut(4, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_PlayerIdle_Attack.bmp"))->Cut(4, 4);
}

void PlayerState_Idle::CreateAnimation(PlayerCharacterType _CharacterType)
{
	//일반 애니메이션
	{
		int ImgXCnt = 2;
		int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

		std::string LeftAniName = MovableActor::LeftStr + IdleAniName.data();
		std::string RightAniName = MovableActor::RightStr + IdleAniName.data();

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
	
	//공격 애니메이션
	{
		int ImgXCnt = 4;
		int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

		std::string LeftAniName = MovableActor::LeftStr + AttackAniName.data();
		std::string RightAniName = MovableActor::RightStr + AttackAniName.data();

		//왼쪽 애니메이션 생성
		GetRender()->CreateAnimation
		({
			.AnimationName = LeftAniName,
			.ImageName = "Left_PlayerIdle_Attack.bmp",
			.Start = AniIndex,
			.End = AniIndex + ImgXCnt - 1,
			.InterTimer = 0.1f,
			.Loop = false
		});

		//오른쪽 애니메이션 생성
		GetRender()->CreateAnimation
		({
			.AnimationName = RightAniName,
			.ImageName = "Right_PlayerIdle_Attack.bmp",
			.Start = AniIndex,
			.End = AniIndex + ImgXCnt - 1,
			.InterTimer = 0.1f,
			.Loop = false
		});
	}

	SetNowAniName(IdleAniName);
}








void PlayerState_Idle::EnterState()
{
	PlayerStateBase::EnterState();
	AccTime = 0.f;
}





void PlayerState_Idle::Update(float _DeltaTime)
{
	//State가 전환된 경우
	if (true == CheckStateChange(_DeltaTime))
		return;

	//플레이어가 공격을 했을때
	CheckAttack();
}



bool PlayerState_Idle::CheckStateChange(float _DeltaTime)
{
	//스테이지가 이동할 때
	if (true == GetRoundLevel()->IsMoving())
	{
		GetFSM()->ChangeState(PlayerStateType::StageMove);
		return true;
	}

	//허공에 떠있는 경우
	if (false == GetPlayer()->IsGround(PlayerBase::CollisionScale))
	{
		GetFSM()->ChangeState(PlayerStateType::Falling);
		return true;
	}

	//점프하는 경우
	if (true == GameEngineInput::IsDown(PLAYER_JUMP))
	{
		GetFSM()->ChangeState(PlayerStateType::Jump);
		return true;
	}

	//움직인 경우
	if (GameEngineInput::IsPress(PLAYER_LEFT) || GameEngineInput::IsPress(PLAYER_RIGHT))
	{
		GetFSM()->ChangeState(PlayerStateType::Move);
		return true;
	}

	
	//idle 상태가 된지 SleepChangeTime시간만큼 흘렀을때
	AccTime += _DeltaTime;
	if (SleepChangeTime < AccTime)
	{
		GetFSM()->ChangeState(PlayerStateType::Sleep);
		return true;
	}

	return false;
}


void PlayerState_Idle::CheckAttack()
{
	//공격 애니메이션이 끝난 경우
	if (true == GetRender()->IsAnimationEnd())
	{
		GetRender()->ChangeAnimation(GetAniNamePlusDir(IdleAniName));
		SetNowAniName(IdleAniName);
	}

	//공격키를 누른경우
	if (false == GameEngineInput::IsDown(PLAYER_ATTACK))
		return;

	CreateBubble();
	GetRender()->ChangeAnimation(GetAniNamePlusDir(AttackAniName), true);
	SetNowAniName(AttackAniName);
	AccTime = 0.0f;
}


void PlayerState_Idle::ExitState()
{
	SetNowAniName(IdleAniName);
}