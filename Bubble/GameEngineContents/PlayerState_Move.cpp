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
	//이 State의 정보 초기화
	PlayerStateBase::Init(
		"Left_PlayerMove.bmp",
		"Right_PlayerMove.bmp",
		"Move",
		std::make_pair(5,4),
		0.08f);

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
	if (true == GameEngineInput::IsDown(PLAYER_JUMP))
	{
		GetOwner()->ChangeState(PlayerStateType::Jump);
		return;
	}

	//방향키 뗀 경우
	if (GameEngineInput::IsFree(PLAYER_LEFT) && GameEngineInput::IsFree(PLAYER_RIGHT))
	{
		GetOwner()->ChangeState(PlayerStateType::Idle);
		return;
	}

	
	//플레이어 방향 체크
	PlayerStateBase::Update(_DeltaTime);

	//다음에 이동할 위치에 벽이 존재하는지 확인
	float4 MoveDir = GetPlayer()->GetDirVec();
	if (true == GetRoundLevel()->IsBlockPos(NowPos + MoveDir * PlayerBase::CollisionScale * 0.5f))
		return;

	//벽이 존재하지 않는다면 이동
	GetPlayer()->SetMove(MoveDir * MoveSpeed * _DeltaTime);
}

