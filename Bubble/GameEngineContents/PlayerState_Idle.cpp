#include "PlayerState_Idle.h"
#include <vector>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsDefine.h"
#include "ContentsEnum.h"
#include "PlayerState.h"
#include "PlayerBase.h"
#include "RoundLevelBase.h"


PlayerState_Idle::PlayerState_Idle()
{

}

PlayerState_Idle::~PlayerState_Idle()
{

}


void PlayerState_Idle::Start(PlayerCharacterType _CharacterType)
{
	//딱 한번만 리소스 로드
	static bool IsLoad = false;
	if (false== IsLoad)
	{
		ResourceLoad("Left_PlayerIdle.bmp", 3, 4);
		ResourceLoad("Right_PlayerIdle.bmp", 3, 4);
		IsLoad = true;
	}

	//현재 Level과 연결
	PlayerStateBase::Start(_CharacterType);

	//애니메이션용 Render 생성 및 이름 설정(여기서 Render크기도 설정)
	SetAniRender("Idle");

	//캐릭터 타입
	int AniIndex = static_cast<int>(_CharacterType) * 3;

	//왼쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = "Left_Idle",
		.ImageName = "Left_PlayerIdle.bmp",
		.Start = AniIndex,
		.End = AniIndex + 1,
		.InterTimer = 0.25f,
	});

	//오른쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = "Right_Idle",
		.ImageName = "Right_PlayerIdle.bmp",
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


void PlayerState_Idle::Update(float _DeltaTime)
{
	//스테이지가 이동할 때
	if (true == GetRoundLevel()->IsMoving())
	{
		GetOwner()->ChangeState(PlayerStateType::StageMove);
		return;
	}

	//공중에 있는 경우
	if (false == GetRoundLevel()->IsBlockPos(GetPlayer()->GetPos() + float4::Down))
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

	//움직인 경우
	if(GameEngineInput::IsPress(PlayerLeft) || GameEngineInput::IsPress(PlayerRight))
	{
		GetOwner()->ChangeState(PlayerStateType::Move);
		return;
	}

	//idle 상태가 된지 SleepChangeTime시간만큼 흘렀을때
	AccTime += _DeltaTime;
	if (SleepChangeTime < AccTime)
	{
		GetOwner()->ChangeState(PlayerStateType::Sleep);
		return;
	}

	//방향에 따라 idle 애니메이션 설정
	PlayerStateBase::Update(_DeltaTime);
}

