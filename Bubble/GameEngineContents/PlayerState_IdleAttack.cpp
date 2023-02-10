#include "PlayerState_IdleAttack.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsDefine.h"
#include "RoundLevelBase.h"
#include "MovableActor.h"
#include "PlayerFSM.h"
#include "PlayerBase.h"


PlayerState_IdleAttack::PlayerState_IdleAttack()
{

}

PlayerState_IdleAttack::~PlayerState_IdleAttack()
{

}

void PlayerState_IdleAttack::Start(PlayerCharacterType _CharacterType)
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

void PlayerState_IdleAttack::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Player");
	Dir.Move("Attack");
	Dir.Move("Idle");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_PlayerIdle_Attack.bmp"))->Cut(4, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_PlayerIdle_Attack.bmp"))->Cut(4, 4);
}

void PlayerState_IdleAttack::CreateAnimation(PlayerCharacterType _CharacterType)
{
	int ImgXCnt = 4;
	int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

	SetAniName("Idle_Attack");
	std::string LeftAniName = MovableActor::LeftStr + GetAniName();
	std::string RightAniName = MovableActor::RightStr + GetAniName();

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

void PlayerState_IdleAttack::Update(float _DeltaTime)
{
	//스테이지가 이동할 때
	if (true == GetRoundLevel()->IsMoving())
	{
		GetOwner()->ChangeState(PlayerStateType::StageMove);
		return;
	}

	//공격 애니메이션이 끝났다면 idle 상태로 전환
	if (true == GetRender()->IsAnimationEnd())
	{
		GetOwner()->ChangeState(PlayerStateType::Idle);
		return;
	}

	//공중에 있는 경우
	if (false == GetRoundLevel()->IsBlockPos(GetPlayer()->GetPos() + float4::Down))
	{
		GetOwner()->ChangeState(PlayerStateType::FallingAttack);
		return;
	}

	//점프하는 경우
	if (true == GameEngineInput::IsDown(PLAYER_JUMP))
	{
		GetOwner()->ChangeState(PlayerStateType::JumpAttack);
		return;
	}

	//움직인 경우
	if (GameEngineInput::IsPress(PLAYER_LEFT) || GameEngineInput::IsPress(PLAYER_RIGHT))
	{
		GetOwner()->ChangeState(PlayerStateType::MoveAttack);
		return;
	}

	

	//방향에 따라 idle 애니메이션 설정
	PlayerStateBase::Update(_DeltaTime);
}