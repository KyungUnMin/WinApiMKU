#include "PlayerState_Falling.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerBase.h"
#include "RoundLevelBase.h"
#include "PlayerState.h"
#include "ContentsDefine.h"

PlayerState_Falling::PlayerState_Falling()
{

}

PlayerState_Falling::~PlayerState_Falling()
{

}

void PlayerState_Falling::Start(PlayerCharacterType _CharacterType)
{
	//딱 한번만 리소스 로드
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad("Left_PlayerFalling.bmp", 2, 4);
		ResourceLoad("Right_PlayerFalling.bmp", 2, 4);
		IsLoad = true;
	}

	//현재 Level과 연결
	PlayerStateBase::Start(_CharacterType);

	//애니메이션용 Render 생성 및 이름 설정(여기서 Render크기도 설정)
	SetAniRender("Falling");


	//캐릭터 타입
	int AniIndex = static_cast<int>(_CharacterType) * 2;

	//왼쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = "Left_Falling",
		.ImageName = "Left_PlayerFalling.bmp",
		.Start = AniIndex,
		.End = AniIndex + 1,
		.InterTimer = 0.25f,
	});

	//오른쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = "Right_Falling",
		.ImageName = "Right_PlayerFalling.bmp",
		.Start = AniIndex,
		.End = AniIndex + 1,
		.InterTimer = 0.25f,
	});

	//방향 받아오기
	const std::string StartDir = GetPlayer()->GetDirStr();

	//현재 방향에 따른 애니메이션 재생 설정
	GetRender()->ChangeAnimation(StartDir + GetAniName());

	//지금은 이 FSM상태가 아닐수 있기 때문에 렌더러 Off
	GetRender()->Off();
}


void PlayerState_Falling::Update(float _DeltaTime)
{
	//스테이지가 이동할 때
	if (true == GetRoundLevel()->IsMoving())
	{
		GetOwner()->ChangeState(PlayerStateType::StageMove);
		return;
	}

	//플레이어의 방향 체크
	PlayerStateBase::Update(_DeltaTime);
	float4 NowPos = GetPlayer()->GetPos();
	float4 MoveDir = GetPlayer()->GetDirVec();

	//떨어지면서도 이동하는 경우에 이동할 위치에 벽이 있는지 확인, 없다면 이동
	if (false == GetRoundLevel()->IsBlockPos(NowPos + MoveDir * MovableActor::ColliderRange))
	{
		GetPlayer()->SetMove(MoveDir * AirMoveSpeed * _DeltaTime);
	}

	//공중에 있는 경우엔 return
	if (false == GetRoundLevel()->IsBlockPos(NowPos + float4::Down))
		return;

	//땅에 닿은 순간에 점프키가 눌려있는 경우
	if (true == GameEngineInput::IsPress(PlayerJump))
	{
		GetOwner()->ChangeState(PlayerStateType::Jump);
		return;
	}

	//그 외에는 정상적으로 땅에 착지 했으므로 Idle
	GetOwner()->ChangeState(PlayerStateType::Idle);
}
