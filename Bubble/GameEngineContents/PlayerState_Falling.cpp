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
	//이 State의 정보 초기화
	PlayerStateBase::Init(
		"Left_PlayerFalling.bmp",
		"Right_PlayerFalling.bmp",
		"Falling",
		std::make_pair(2, 4),
		0.25f);

	//딱 한번만 리소스 로드
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		PlayerStateBase::ResourceLoad();
		IsLoad = true;
	}

	//애니메이션 생성 및 RoundLevel과 연결
	PlayerStateBase::Start(_CharacterType);
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

	//떨어지면서도 이동하는 경우에 
	if (GameEngineInput::IsPress(PlayerRight) || GameEngineInput::IsPress(PlayerLeft))
	{
		//이동할 위치에 벽이 있는지 확인, 없다면 이동
		if (false == GetRoundLevel()->IsBlockPos(NowPos + MoveDir * MovableActor::ColliderRange))
		{
			GetPlayer()->SetMove(MoveDir * AirMoveSpeed * _DeltaTime);
		}
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
