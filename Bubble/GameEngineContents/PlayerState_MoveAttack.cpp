#include "PlayerState_MoveAttack.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsDefine.h"
#include "RoundLevelBase.h"
#include "MovableActor.h"
#include "PlayerFSM.h"
#include "PlayerBase.h"

PlayerState_MoveAttack::PlayerState_MoveAttack()
{

}

PlayerState_MoveAttack::~PlayerState_MoveAttack()
{

}


void PlayerState_MoveAttack::Start(PlayerCharacterType _CharacterType)
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



void PlayerState_MoveAttack::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Player");
	Dir.Move("Attack");
	Dir.Move("Move");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_PlayerMove_Attack.bmp"))->Cut(4, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_PlayerMove_Attack.bmp"))->Cut(4, 4);
}

void PlayerState_MoveAttack::CreateAnimation(PlayerCharacterType _CharacterType)
{
	int ImgXCnt = 4;
	int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

	SetAniName("Move_Attack");
	std::string LeftAniName = MovableActor::LeftStr + GetAniName();
	std::string RightAniName = MovableActor::RightStr + GetAniName();

	//왼쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = "Left_PlayerMove_Attack.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.1f,
		.Loop = false
	});

	//오른쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = RightAniName,
		.ImageName = "Right_PlayerMove_Attack.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.1f,
		.Loop = false
	});
}


void PlayerState_MoveAttack::Update(float _DeltaTime)
{
	//스테이지가 이동할 때
	if (true == GetRoundLevel()->IsMoving())
	{
		GetOwner()->ChangeState(PlayerStateType::StageMove);
		return;
	}

	//공격 애니메이션이 끝났다면
	if (true == GetRender()->IsAnimationEnd())
	{
		GetOwner()->ChangeState(PlayerStateType::Move);
		return;
	}

	//공중에 있는 경우
	float4 NowPos = GetPlayer()->GetPos();
	if (false == GetRoundLevel()->IsBlockPos(NowPos + float4::Down))
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

	//방향키 뗀 경우
	if (GameEngineInput::IsFree(PLAYER_LEFT) && GameEngineInput::IsFree(PLAYER_RIGHT))
	{
		GetOwner()->ChangeState(PlayerStateType::IdleAttack);
		return;
	}

	


	//플레이어 방향 체크
	PlayerStateBase::Update(_DeltaTime);

	//다음에 이동할 위치에 벽이 존재하는지 확인
	float4 MoveDir = GetPlayer()->GetDirVec();
	if (true == GetRoundLevel()->IsBlockPos(NowPos + MoveDir * PlayerBase::CollisionScale * 0.5f))
		return;

	//벽이 존재하지 않는다면 이동
	GetPlayer()->SetMove(MoveDir * PlayerState_Move::MoveSpeed * _DeltaTime);
}