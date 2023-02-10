#include "PlayerState_FallingAttack.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsDefine.h"
#include "RoundLevelBase.h"
#include "MovableActor.h"
#include "PlayerFSM.h"
#include "PlayerBase.h"


PlayerState_FallingAttack::PlayerState_FallingAttack()
{

}

PlayerState_FallingAttack::~PlayerState_FallingAttack()
{

}


void PlayerState_FallingAttack::Start(PlayerCharacterType _CharacterType)
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



void PlayerState_FallingAttack::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Player");
	Dir.Move("Attack");
	Dir.Move("Falling");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_PlayerFalling_Attack.bmp"))->Cut(4, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_PlayerFalling_Attack.bmp"))->Cut(4, 4);
}

void PlayerState_FallingAttack::CreateAnimation(PlayerCharacterType _CharacterType)
{
	int ImgXCnt = 4;
	int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

	SetAniName("Falling_Attack");
	std::string LeftAniName = MovableActor::LeftStr + GetAniName();
	std::string RightAniName = MovableActor::RightStr + GetAniName();

	//왼쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = "Left_PlayerFalling_Attack.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.1f,
		.Loop = false
	});

	//오른쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = RightAniName,
		.ImageName = "Right_PlayerFalling_Attack.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.1f,
		.Loop = false
	});
}



void PlayerState_FallingAttack::Update(float _DeltaTime)
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
		GetOwner()->ChangeState(PlayerStateType::Falling);
		return;
	}

	//플레이어의 방향 체크
	PlayerStateBase::Update(_DeltaTime);
	float4 NowPos = GetPlayer()->GetPos();
	float4 MoveDir = GetPlayer()->GetDirVec();

	//떨어지면서도 이동하는 경우에 
	if (GameEngineInput::IsPress(PLAYER_RIGHT) || GameEngineInput::IsPress(PLAYER_LEFT))
	{
		//이동할 위치에 벽이 있는지 확인, 없다면 이동
		if (false == GetRoundLevel()->IsBlockPos(NowPos + MoveDir * PlayerBase::CollisionScale * 0.5f))
		{
			GetPlayer()->SetMove(MoveDir * PlayerState_Falling::AirMoveSpeed * _DeltaTime);
		}
	}


	//공중에 있는 경우엔 return
	if (false == GetRoundLevel()->IsBlockPos(NowPos + float4::Down))
		return;

	if (true == GetRoundLevel()->IsBlockPos(NowPos))
		return;

	////땅에 닿은 순간에 점프키가 눌려있는 경우
	//if (true == GameEngineInput::IsPress(PLAYER_JUMP))
	//{
	//	GetOwner()->ChangeState(PlayerStateType::JumpAttack);
	//	return;
	//}

	//그 외에는 정상적으로 땅에 착지 했으므로 Idle
	GetOwner()->ChangeState(PlayerStateType::Idle);
}