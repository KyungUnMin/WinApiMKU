#include "PlayerState_Move.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerBase.h"
#include "ContentsDefine.h"
#include "PlayerFSM.h"
#include "RoundLevelBase.h"

PlayerState_Move::PlayerState_Move()
{

}

PlayerState_Move::~PlayerState_Move()
{

}

void PlayerState_Move::Start(PlayerCharacterType _CharacterType)
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





void PlayerState_Move::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Player");
	Dir.Move("Move");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_PlayerMove.bmp"))->Cut(5, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_PlayerMove.bmp"))->Cut(5, 4);
}


void PlayerState_Move::CreateAnimation(PlayerCharacterType _CharacterType)
{
	int ImgXCnt = 5;
	int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

	SetAniName("Move");
	std::string LeftAniName = MovableActor::LeftStr + GetAniName();
	std::string RightAniName = MovableActor::RightStr + GetAniName();

	//왼쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = "Left_PlayerMove.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.08f,
	});

	//오른쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = RightAniName,
		.ImageName = "Right_PlayerMove.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.08f,
	});
}



void PlayerState_Move::Update(float _DeltaTime)
{
	//스테이지가 이동할 때
	if (true == GetRoundLevel()->IsMoving())
	{
		GetFSM()->ChangeState(PlayerStateType::StageMove);
		return;
	}

	//공격키를 누른 경우
	if (true == GameEngineInput::IsDown(PLAYER_ATTACK))
	{
		GetFSM()->ChangeState(PlayerStateType::MoveAttack);
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

	//방향키 뗀 경우
	if (GameEngineInput::IsFree(PLAYER_LEFT) && GameEngineInput::IsFree(PLAYER_RIGHT))
	{
		GetFSM()->ChangeState(PlayerStateType::Idle);
		return;
	}

	//플레이어의 방향이 바뀌였다면 그 방향에 따라 애니메이션 전환
	ChangeAniDir();

	//플레이어 이동
	GetPlayer()->MoveHorizon(MoveSpeed.x, PlayerBase::CollisionScale, _DeltaTime);
}


