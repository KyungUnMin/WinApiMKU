#include "PlayerState_Damaged.h"
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerBase.h"
#include "PlayerState.h"

PlayerState_Damaged::PlayerState_Damaged()
{

}

PlayerState_Damaged::~PlayerState_Damaged()
{

}

void PlayerState_Damaged::Start(PlayerCharacterType _CharacterType)
{
	//딱 한번만 리소스 로드
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad("Left_PlayerDamaged.bmp", ImgColCnt, 4);
		ResourceLoad("Right_PlayerDamaged.bmp", ImgColCnt, 4);
		IsLoad = true;
	}

	
	
	//현재 Level과 연결
	PlayerStateBase::Start(_CharacterType);

	//애니메이션용 Render 생성 및 이름 설정(여기서 Render크기도 설정)
	SetAniRender("Damaged");



	//캐릭터 타입
	int AniIndex = static_cast<int>(_CharacterType) * ImgColCnt;

	//왼쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = "Left_Damaged",
		.ImageName = "Left_PlayerDamaged.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgColCnt - 1,
		.InterTimer = 0.1f,
		.Loop = false
	});

	//오른쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = "Right_Damaged",
		.ImageName = "Right_PlayerDamaged.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgColCnt - 1,
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

void PlayerState_Damaged::Update(float _DeltaTime)
{
	//애니메이션이 끝날때까지 대기
	if (false == GetRender()->IsAnimationEnd())
		return;

	

	//플레이어 생명력을 감소시키고 플레이어가 살아있다면
	if (true == GetPlayer()->DecreaseLife())
	{
		GetOwner()->ChangeState(PlayerStateType::Idle);
		//GetPlayer()->SetPos(GetRoundLevel()->)
		return;
	}

	//플레이어가 죽었을때
	GetPlayer()->Death();

	//TODO
	//GetRoundLevel()->
}

void PlayerState_Damaged::EnterState()
{
	const std::string StartDir = GetPlayer()->GetDirStr();
	GetRender()->ChangeAnimation(StartDir + GetAniName(), true);
	GetRender()->On();
}

