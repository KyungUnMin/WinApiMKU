#include "PlayerState_Sleep.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerBase.h"
#include "ContentsDefine.h"
#include "PlayerState.h"
#include "RoundLevelBase.h"

PlayerState_Sleep::PlayerState_Sleep()
{

}

PlayerState_Sleep::~PlayerState_Sleep()
{

}

void PlayerState_Sleep::Start(PlayerCharacterType _CharacterType)
{
	bool AniLoop = true;
	if (_CharacterType == PlayerCharacterType::CORORON || _CharacterType == PlayerCharacterType::KULULUN)
	{
		AniLoop = false;
	}

	//이 State의 정보 초기화
	PlayerStateBase::Init(
		"Left_PlayerSleep.bmp",
		"Right_PlayerSleep.bmp",
		"Sleep",
		std::make_pair(3, 4),
		0.25f, AniLoop);

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

void PlayerState_Sleep::Update(float _DeltaTime)
{
	//스테이지 전환중일때
	if (true == GetRoundLevel()->IsMoving())
	{
		GetOwner()->ChangeState(PlayerStateType::StageMove);
		return;
	}

	//점프키를 눌렀을때
	if (true == GameEngineInput::IsDown(PLAYER_JUMP))
	{
		GetOwner()->ChangeState(PlayerStateType::Jump);
		return;
	}

	//왼쪽 또는 오른쪽으로 이동하려고 했을때
	if (GameEngineInput::IsPress(PLAYER_RIGHT) || GameEngineInput::IsPress(PLAYER_LEFT))
	{
		GetOwner()->ChangeState(PlayerStateType::Move);
		return;
	}
}
