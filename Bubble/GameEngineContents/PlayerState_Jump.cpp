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
}


void PlayerState_Jump::CreateAnimation(PlayerCharacterType _CharacterType)
{
	int ImgXCnt = 4;
	int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

	SetAniName("Jump");
	std::string LeftAniName = MovableActor::LeftStr + GetAniName();
	std::string RightAniName = MovableActor::RightStr + GetAniName();

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










void PlayerState_Jump::EnterState()
{
	PlayerStateBase::EnterState();
	AccTime = 0.0f;
}


void PlayerState_Jump::Update(float _DeltaTime)
{
	if (true == CheckStateChange(_DeltaTime))
		return;

	Move(_DeltaTime);
}



bool PlayerState_Jump::CheckStateChange(float _DeltaTime)
{
	//스테이지가 이동할 때
	if (true == GetRoundLevel()->IsMoving())
	{
		GetFSM()->ChangeState(PlayerStateType::StageMove);
		return true;
	}

	//공격키를 눌렀을 때
	if (true == GameEngineInput::IsDown(PLAYER_ATTACK))
	{
		//이러면 JumpAttack은 얼마나 점프를 유지해야 하지???
		GetFSM()->ChangeState(PlayerStateType::JumpAttack);
		return true;
	}

	//시간 세기
	AccTime += _DeltaTime;

	//점프 유지 시간이 전부 지났을때
	if (FallingChangeTime < AccTime)
	{
		GetFSM()->ChangeState(PlayerStateType::Falling);
		return true;
	}

	return false;
}




void PlayerState_Jump::Move(float _DeltaTime)
{
	//플레이어의 방향이 바뀌였다면 그 방향에 따라 애니메이션 전환
	ChangeAniDir();

	float4 NowPos = GetPlayer()->GetPos();
	float4 NextPos = NowPos + (float4::Up * JumpSpeed * _DeltaTime);
	float4 CollisionScale = PlayerBase::CollisionScale;
	float PlayerHeight = CollisionScale.Size();

	//다음에 이동할 위치가 스크린을 넘어가지 않을때만
	if (NextPos.y - PlayerHeight < ScreenTopOffset)
		return;

	GetPlayer()->SetPos(NextPos);


	//점프중에도 플레이어를 이동키실때
	if (GameEngineInput::IsPress(PLAYER_RIGHT) || GameEngineInput::IsPress(PLAYER_LEFT))
	{
		GetPlayer()->MoveHorizon(AirMoveSpeed.x, PlayerBase::CollisionScale, _DeltaTime);
	}
}
