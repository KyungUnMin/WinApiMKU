#include "PlayerState_Move.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerBase.h"
#include "ContentsDefine.h"
#include "PlayerState.h"
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
		ResourceLoad("Left_PlayerMove.bmp", 5, 4);
		ResourceLoad("Right_PlayerMove.bmp", 5, 4);
		IsLoad = true;
	}

	//현재 Level과 연결
	PlayerStateBase::Start(_CharacterType);

	//애니메이션용 Render 생성 및 이름 설정(여기서 Render크기도 설정)
	SetAniRender("Move");

	//캐릭터 타입
	int AniIndex = static_cast<int>(_CharacterType) * 5;

	//왼쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = "Left_Move",
		.ImageName = "Left_PlayerMove.bmp",
		.Start = AniIndex,
		.End = AniIndex + 4,
		.InterTimer = AniInterval,
	});

	//오른쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = "Right_Move",
		.ImageName = "Right_PlayerMove.bmp",
		.Start = AniIndex,
		.End = AniIndex + 4,
		.InterTimer = AniInterval,
	});

	//방향 받아오기
	const std::string StartDir = GetPlayer()->GetDirStr();

	//현재 방향에 따른 애니메이션 재생 설정
	GetRender()->ChangeAnimation(StartDir + GetAniName());

	//지금은 이 FSM상태가 아닐수 있기 때문에 렌더러 Off
	GetRender()->Off();
}


void PlayerState_Move::Update(float _DeltaTime)
{
	//스테이지가 이동할 때
	if (true == GetRoundLevel()->IsMoving())
	{
		GetOwner()->ChangeState(PlayerStateType::StageMove);
		return;
	}


	//공중에 있는 경우
	float4 NowPos = GetPlayer()->GetPos();
	if (false == GetRoundLevel()->IsBlockPos(NowPos + float4::Down))
	{
		GetOwner()->ChangeState(PlayerStateType::Falling);
		return;
	}

	//점프하는 경우
	if (true == GameEngineInput::IsDown(PlayerJump))
	{
		GetOwner()->ChangeState(PlayerStateType::Jump);
		return;
	}

	//방향키 뗀 경우
	if (GameEngineInput::IsFree(PlayerLeft) && GameEngineInput::IsFree(PlayerRight))
	{
		GetOwner()->ChangeState(PlayerStateType::Idle);
		return;
	}

	
	//플레이어 방향 체크
	PlayerStateBase::Update(_DeltaTime);

	//다음에 이동할 위치에 벽이 존재하는지 확인
	float4 MoveDir = GetPlayer()->GetDirVec();
	if (true == GetRoundLevel()->IsBlockPos(NowPos + MoveDir * MovableActor::ColliderRange))
		return;

	//벽이 존재하지 않는다면 이동
	GetPlayer()->SetMove(MoveDir * MoveSpeed * _DeltaTime);
}

