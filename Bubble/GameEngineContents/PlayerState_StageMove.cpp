#include "PlayerState_StageMove.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineRender.h>
#include "RoundLevelBase.h"
#include "PlayerBase.h"
#include "PlayerState.h"

PlayerState_StageMove::PlayerState_StageMove()
{

}

PlayerState_StageMove::~PlayerState_StageMove()
{

}

void PlayerState_StageMove::Start(PlayerCharacterType _CharacterType)
{
	//딱 한번만 리소스 로드
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad("PlayerStageMove.bmp", 3, 4);
		ResourceLoad("StageMoveBubble.bmp", 3, 1);
		IsLoad = true;
	}

	//현재 Level과 연결
	PlayerStateBase::Start(_CharacterType);

	//플레이어 애니메이션 생성(private)
	CreatePlayerAni(_CharacterType);

	//뒤쪽 투명 거품 애니메이션 생성(private)
	CreateBubbleAni();
}

void PlayerState_StageMove::CreatePlayerAni(PlayerCharacterType _CharacterType)
{
	//렌더러 생성 및 크기 조절
	SetAniRender("StageMove");
	int AniIndex = static_cast<int>(_CharacterType) * 3;

	//애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = "StageMove",
		.ImageName = "PlayerStageMove.bmp",
		.Start = AniIndex,
		.End = AniIndex + 2,
		.InterTimer = 0.1f,
	});

	//애니메이션 재생 설정
	GetRender()->ChangeAnimation(GetAniName());
	//지금은 이 FSM상태가 아닐수 있기 때문에 렌더러 Off
	GetRender()->Off();
}

void PlayerState_StageMove::CreateBubbleAni()
{
	//플레이어에 Render객체 생성한 후 받아오기
	ClearBubble = GetPlayer()->CreateRender(RoundRenderOrder::ClearBubble);

	//애니메이션 생성
	ClearBubble->CreateAnimation
	({
		.AnimationName = "ClearBubble",
		.ImageName = "StageMoveBubble.bmp",
		.Start = 0,
		.End = 2,
		.InterTimer = 0.1f,
	});

	//크기 조정
	ClearBubble->SetScale({ 200.f, 200.f });
	//애니메이션 재생 설정
	ClearBubble->ChangeAnimation("ClearBubble");
	//지금은 이 FSM상태가 아닐수 있기 때문에 렌더러 Off
	ClearBubble->Off();
	//위치값 설정
	ClearBubble->SetPosition(float4::Up * 30.f);
}


void PlayerState_StageMove::Update(float _DeltaTime)
{

	//현재 레벨의 Stage가 전환중이라면 플레이어를 이동시킨다
	if (true == GetRoundLevel()->IsMoving())
	{
		float StageMoveTime = GetRoundLevel()->GetStageMoveTime();
		float Ratio = StageMoveTime / RoundLevelBase::StageMoveDuration;

		float4 DestPos = GetRoundLevel()->GetPlayerSpawnPos();
		float4 NextPos = float4::LerpClamp(PlayerOriginPos, DestPos, Ratio);
		GetPlayer()->SetPos(NextPos);
		return;
	}
	
	//현재 레벨의 Stage 전환이 끝났다면 Idle상태로 전환
	GetOwner()->ChangeState(PlayerStateType::Idle);
}

//플레이어 애니메이션 켜기 & 뒤쪽 거품 켜기
void PlayerState_StageMove::EnterState()
{
	//Stage가 전환될때 처음 플레이어 위치 기록
	PlayerOriginPos = GetPlayer()->GetPos();

	GetRender()->On();
	ClearBubble->On();
}

//플레이어 애니메이션 끄기 & 뒤쪽 거품 끄기
void PlayerState_StageMove::ExitState()
{
	GetRender()->Off();
	ClearBubble->Off();
}

