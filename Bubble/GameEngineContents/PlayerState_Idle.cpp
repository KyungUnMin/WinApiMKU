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
	//이 State의 정보 초기화
	PlayerStateBase::Init(
		"Left_PlayerIdle.bmp",
		"Right_PlayerIdle.bmp",
		"Idle",
		std::make_pair(2, 4),
		0.25f);

	//딱 한번만 리소스 로드
	static bool IsLoad = false;
	if (false== IsLoad)
	{
		PlayerStateBase::ResourceLoad();
		IsLoad = true;
	}

	//애니메이션 생성 및 RoundLevel과 연결
	PlayerStateBase::Start(_CharacterType);

	//테스트 코드
	if (false == GameEngineInput::IsKey("Test_PlayerDamaged"))
		GameEngineInput::CreateKey("Test_PlayerDamaged", 'K');
}


void PlayerState_Idle::Update(float _DeltaTime)
{
	//테스트 코드
	if (true == GameEngineInput::IsDown("Test_PlayerDamaged"))
	{
		GetOwner()->ChangeState(PlayerStateType::Damaged);
		return;
	}

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
	if (true == GameEngineInput::IsDown(PLAYER_JUMP))
	{
		GetOwner()->ChangeState(PlayerStateType::Jump);
		return;
	}

	//움직인 경우
	if(GameEngineInput::IsPress(PLAYER_LEFT) || GameEngineInput::IsPress(PLAYER_RIGHT))
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

