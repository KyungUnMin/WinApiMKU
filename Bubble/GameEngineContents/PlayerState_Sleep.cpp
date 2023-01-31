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
	//딱 한번만 리소스 로드
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad("Left_PlayerSleep.bmp", 3, 4);
		ResourceLoad("Right_PlayerSleep.bmp", 3, 4);
		IsLoad = true;
	}

	//현재 Level과 연결
	PlayerStateBase::Start(_CharacterType);

	//애니메이션용 Render 생성 및 Render크기 설정
	SetAniRender("Sleep");

	//캐릭터 타입
	int AniIndex = static_cast<int>(_CharacterType) * 3;

	//캐릭터가 CORORON 이거나 KULULUN인 경우엔 애니메이션을 반복재생하지 않음
	bool Repeat = true;
	if (_CharacterType == PlayerCharacterType::CORORON || 
		_CharacterType == PlayerCharacterType::KULULUN)
	{
		Repeat = false;
	}

	//왼쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = "Left_Sleep",
		.ImageName = "Left_PlayerSleep.bmp",
		.Start = AniIndex,
		.End = AniIndex + 2,
		.InterTimer = 0.25f,
		.Loop = Repeat
	});

	//오른쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = "Right_Sleep",
		.ImageName = "Right_PlayerSleep.bmp",
		.Start = AniIndex,
		.End = AniIndex + 2,
		.InterTimer = 0.25f,
		.Loop = Repeat
	});

	//방향 받아오기
	const std::string StartDir = GetPlayer()->GetDirStr();

	//현재 방향에 따른 애니메이션 재생 설정
	GetRender()->ChangeAnimation(StartDir + GetAniName());

	//지금은 이 FSM상태가 아닐수 있기 때문에 렌더러 Off
	GetRender()->Off();
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
	if (true == GameEngineInput::IsDown(PlayerJump))
	{
		GetOwner()->ChangeState(PlayerStateType::Jump);
		return;
	}

	//왼쪽 또는 오른쪽으로 이동하려고 했을때
	if (GameEngineInput::IsPress(PlayerRight) || GameEngineInput::IsPress(PlayerLeft))
	{
		GetOwner()->ChangeState(PlayerStateType::Move);
		return;
	}
}
