#include "PlayerState_Jump.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerState.h"
#include "PlayerBase.h"
#include "RoundLevelBase.h"
#include "ContentsDefine.h"

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
		ResourceLoad("Left_PlayerJump.bmp", 4, 4);
		ResourceLoad("Right_PlayerJump.bmp", 4, 4);
		IsLoad = true;
	}

	//현재 Level과 연결
	PlayerStateBase::Start(_CharacterType);

	//애니메이션용 Render 생성 및 이름 설정(여기서 Render크기도 설정)
	SetAniRender("Jump");


	//캐릭터 타입
	int AniIndex = static_cast<int>(_CharacterType) * 4;

	//왼쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = "Left_Jump",
		.ImageName = "Left_PlayerJump.bmp",
		.Start = AniIndex,
		.End = AniIndex + 3,
		.InterTimer = 0.1f,
		.Loop = false
	});

	//오른쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = "Right_Jump",
		.ImageName = "Right_PlayerJump.bmp",
		.Start = AniIndex,
		.End = AniIndex + 3,
		.InterTimer = 0.1f,
		.Loop = false
	});

	//방향 받아오기
	const std::string StartDir = GetPlayer()->GetDirStr();

	//현재 방향에 따른 애니메이션 재생 설정
	GetRender()->ChangeAnimation(StartDir + GetAniName());

	//지금은 이 FSM상태가 아닐수 있기 때문에 렌더러 Off
	GetRender()->Off();
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
	if (0.f <= GetPlayer()->GetGravityAcc())
	{
		GetOwner()->ChangeState(PlayerStateType::Falling);
		return;
	}

	//플레이어 방향 체크
	PlayerStateBase::Update(_DeltaTime);

	//점프중에도 플레이어를 이동키실때
	if (GameEngineInput::IsPress(PlayerRight) || GameEngineInput::IsPress(PlayerLeft))
	{
		float4 NowPos = GetPlayer()->GetPos();
		float4 MoveDir = GetPlayer()->GetDirVec();

		//이동시키는 위치가 벽이 아니라면 이동
		if (false == GetRoundLevel()->IsBlockPos(NowPos + MoveDir * MovableActor::ColliderRange))
		{
			GetPlayer()->SetMove(MoveDir * AirMoveSpeed * _DeltaTime);
		}
	}
	
}

void PlayerState_Jump::EnterState()
{
	PlayerStateBase::EnterState();
	GetPlayer()->SetMove(float4::Up);
	GetPlayer()->SetGravityAcc(-JumpAcc);
}
