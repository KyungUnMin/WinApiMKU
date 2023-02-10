#include "PlayerState_JumpAttack.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include "PlayerFSM.h"
#include "PlayerBase.h"
#include "RoundLevelBase.h"
#include "ContentsDefine.h"
#include "Gravity.h"

PlayerState_JumpAttack::PlayerState_JumpAttack()
{

}

PlayerState_JumpAttack::~PlayerState_JumpAttack()
{

}

void PlayerState_JumpAttack::Start(PlayerCharacterType _CharacterType)
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


void PlayerState_JumpAttack::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Player");
	Dir.Move("Attack");
	Dir.Move("Jump");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_PlayerJump_Attack.bmp"))->Cut(4, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_PlayerJump_Attack.bmp"))->Cut(4, 4);
}

void PlayerState_JumpAttack::CreateAnimation(PlayerCharacterType _CharacterType)
{
	int ImgXCnt = 4;
	int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

	SetAniName("Jump_Attack");
	std::string LeftAniName = MovableActor::LeftStr + GetAniName();
	std::string RightAniName = MovableActor::RightStr + GetAniName();

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

void PlayerState_JumpAttack::Update(float _DeltaTime)
{
	//스테이지가 이동할 때
	if (true == GetRoundLevel()->IsMoving())
	{
		GetOwner()->ChangeState(PlayerStateType::StageMove);
		return;
	}

	if (true == GetRender()->IsAnimationEnd())
	{
		GetOwner()->ChangeState(PlayerStateType::Jump);
		return;
	}

	//점프위치가 최고점에 닿았을때
	if (0.f <= GetPlayer()->GetGravity()->GetAcc())
	{
		GetOwner()->ChangeState(PlayerStateType::FallingAttack);
		return;
	}


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
			GetPlayer()->SetMove(MoveDir * PlayerState_Jump::AirMoveSpeed * _DeltaTime);
		}
	}
}
