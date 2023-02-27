#include "PlayerState_Jump.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include "PlayerFSM.h"
#include "PlayerBase.h"
#include "RoundLevelBase.h"
#include "ContentsDefine.h"
#include "Gravity.h"

PlayerState_Jump::PlayerState_Jump()
{

}

PlayerState_Jump::~PlayerState_Jump()
{

}

void PlayerState_Jump::Start(PlayerCharacterType _CharacterType)
{
	//딱 한번만 리소스 로드
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad();
		LoadSFX();
		IsLoad = true;
	}

	ConnectRoundLevel();
	CreateAnimation(_CharacterType);
}




void PlayerState_Jump::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Player");
	Dir.Move("Jump");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_PlayerJump.bmp"))->Cut(4, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_PlayerJump.bmp"))->Cut(4, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_PlayerJump_Attack.bmp"))->Cut(4, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_PlayerJump_Attack.bmp"))->Cut(4, 4);
}

void PlayerState_Jump::LoadSFX()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");
	Dir.Move("SFX");
	Dir.Move("Player");
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("PlayerJump.wav"));
}


void PlayerState_Jump::CreateAnimation(PlayerCharacterType _CharacterType)
{
	//일반 애니메이션
	{
		int ImgXCnt = 4;
		int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

		std::string LeftAniName = MovableActor::LeftStr + JumpAniName.data();
		std::string RightAniName = MovableActor::RightStr + JumpAniName.data();

		//왼쪽 애니메이션 생성
		GetRender()->CreateAnimation
		({
			.AnimationName = LeftAniName,
			.ImageName = "Left_PlayerJump.bmp",
			.Start = AniIndex,
			.End = AniIndex + ImgXCnt - 1,
			.InterTimer = 0.1f,
		});

		//오른쪽 애니메이션 생성
		GetRender()->CreateAnimation
		({
			.AnimationName = RightAniName,
			.ImageName = "Right_PlayerJump.bmp",
			.Start = AniIndex,
			.End = AniIndex + ImgXCnt - 1,
			.InterTimer = 0.1f,
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
			.ImageName = "Left_PlayerJump_Attack.bmp",
			.Start = AniIndex,
			.End = AniIndex + ImgXCnt - 1,
			.InterTimer = 0.1f,
			.Loop = false
		});

		//오른쪽 애니메이션 생성
		GetRender()->CreateAnimation
		({
			.AnimationName = RightAniName,
			.ImageName = "Right_PlayerJump_Attack.bmp",
			.Start = AniIndex,
			.End = AniIndex + ImgXCnt - 1,
			.InterTimer = 0.1f,
			.Loop = false
		});
	}

	SetNowAniName(JumpAniName);
}










void PlayerState_Jump::EnterState()
{
	PlayerStateBase::EnterState();
	GameEngineResources::GetInst().SoundPlay("PlayerJump.wav");
	AccTime = 0.0f;
}



void PlayerState_Jump::Update(float _DeltaTime)
{
	//플레이어의 방향이 바뀌였다면 그 방향에 따라 애니메이션 전환
	ChangeAniDir();

	//시간 세기
	AccTime += _DeltaTime;

	if (true == CheckStateChange(_DeltaTime))
		return;

	CheckAttack();
}



bool PlayerState_Jump::CheckStateChange(float _DeltaTime)
{
	//스테이지가 이동할 때
	if (true == GetRoundLevel()->IsMoving())
	{
		GetFSM()->ChangeState(PlayerStateType::StageMove);
		return true;
	}

	//점프 유지 시간이 전부 지났을때
	if (FallingChangeTime < AccTime)
	{
		GetFSM()->ChangeState(PlayerStateType::Falling);
		return true;
	}

	//움직이다가 점프를 못하는 상황일때
	if (false == Movement(_DeltaTime))
	{
		GetFSM()->ChangeState(PlayerStateType::Falling);
		return true;
	}

	return false;
}




bool PlayerState_Jump::Movement(float _DeltaTime)
{
	float Ratio = AccTime / FallingChangeTime;
	float4 NowJumpSpeed = float4::LerpClamp(JumpSpeed, float4::Zero, Ratio);

	float4 NowPos = GetPlayer()->GetPos();
	float4 NextPos = NowPos + (float4::Up * NowJumpSpeed * _DeltaTime);
	float4 CollisionScale = PlayerBase::CollisionScale;
	float PlayerHeight = CollisionScale.Size();

	//다음에 이동할 위치가 스크린을 넘어간다면
	/*if (NextPos.y - PlayerHeight < ScreenTopOffset)
		return false;*/

	GetPlayer()->SetPos(NextPos);


	//점프중에도 플레이어를 이동키실때
	if (GameEngineInput::IsPress(PLAYER_RIGHT) || GameEngineInput::IsPress(PLAYER_LEFT))
	{
		//점프의 경우 MoveHorizon안에 벽을 뛰어넘을수 있는 범위의 함수를 오버로딩하면
		//중간에 걸리는 느낌을 없앨수 있을것 같다.(추후에 생각해보자)
		GetPlayer()->MoveHorizon(AirMoveSpeed.x, PlayerBase::CollisionScale, _DeltaTime);
	}

	return true;
}



void PlayerState_Jump::CheckAttack()
{
	//공격 애니메이션이 끝난 경우
	if (true == GetRender()->IsAnimationEnd())
	{
		GetRender()->ChangeAnimation(GetAniNamePlusDir(JumpAniName));
		SetNowAniName(JumpAniName);
	}

	//공격키를 누른 경우만
	if (false == GameEngineInput::IsDown(PLAYER_ATTACK))
		return;

	CreateBubble();
	GetRender()->ChangeAnimation(GetAniNamePlusDir(AttackAniName), true);
	SetNowAniName(AttackAniName);
}

void PlayerState_Jump::ExitState()
{
	SetNowAniName(JumpAniName);
}
