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

void PlayerState_Jump::Update(float _DeltaTime)
{
	//스테이지가 이동할 때
	if (true == GetRoundLevel()->IsMoving())
	{
		GetOwner()->ChangeState(PlayerStateType::StageMove);
		return;
	}

	//점프위치가 최고점에 닿았을때
	if (0.f <= GetPlayer()->GetGravity()->GetAcc())
	{
		GetOwner()->ChangeState(PlayerStateType::Falling);
		return;
	}

	////플레이어 바로 위가 벽일때
	//float4 UpPos = GetPlayer()->GetPos() + float4::Up;
	//if (GetRoundLevel()->IsBlockPos(UpPos))
	//{
	//	GetPlayer()->SetGravityAcc(0.f);
	//	GetOwner()->ChangeState(PlayerStateType::Falling);
	//	return;
	//}


	//플레이어 방향 체크
	PlayerStateBase::Update(_DeltaTime);

	//점프중에도 플레이어를 이동키실때
	if (GameEngineInput::IsPress(PLAYER_RIGHT) || GameEngineInput::IsPress(PLAYER_LEFT))
	{
		float4 NowPos = GetPlayer()->GetPos();
		float4 MoveDir = GetPlayer()->GetDirVec();

		//이동시키는 위치가 벽이 아니라면 이동
		if (false == GetRoundLevel()->IsBlockPos(NowPos + MoveDir * PlayerBase::CollisionScale * 0.5f))
		{
			GetPlayer()->SetMove(MoveDir * AirMoveSpeed * _DeltaTime);
		}
	}
	
}

void PlayerState_Jump::EnterState()
{
	PlayerStateBase::EnterState();
	GetPlayer()->SetMove(float4::Up);
	GetPlayer()->GetGravity()->SetAcc(-JumpAcc);
}



void PlayerState_Jump::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Player");
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
