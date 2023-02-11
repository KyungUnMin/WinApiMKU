#include "PlayerState_StageMove.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include "RoundLevelBase.h"
#include "PlayerBase.h"
#include "PlayerFSM.h"
#include "Gravity.h"

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
		ResourceLoad();
		IsLoad = true;
	}

	ConnectRoundLevel();
	CreateAnimation(_CharacterType);

	//뒤쪽 투명 거품 애니메이션 생성(private)
	CreateBubbleAni();
}


void PlayerState_StageMove::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Player");
	Dir.Move("StageMove");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_PlayerStageMove.bmp"))->Cut(3, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_PlayerStageMove.bmp"))->Cut(3, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("StageMoveBubble.bmp"))->Cut(3, 1);
}

void PlayerState_StageMove::CreateAnimation(PlayerCharacterType _CharacterType)
{
	int ImgXCnt = 3;
	int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

	SetAniName("StageMove");
	std::string LeftAniName = MovableActor::LeftStr + GetAniName();
	std::string RightAniName = MovableActor::RightStr + GetAniName();

	//왼쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = "Left_PlayerStageMove.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.1f,
	});

	//오른쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = RightAniName,
		.ImageName = "Right_PlayerStageMove.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.1f,
	});
}

void PlayerState_StageMove::CreateBubbleAni()
{
	//플레이어에 Render객체 생성한 후 받아오기
	ClearBubble = GetPlayer()->CreateRender(RenderOrder::ClearBubble);

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



//플레이어 애니메이션 켜기 & 뒤쪽 거품 켜기
void PlayerState_StageMove::EnterState()
{
	PlayerStateBase::EnterState();

	//Stage가 전환될때 처음 플레이어 위치 기록
	PlayerOriginPos = GetPlayer()->GetPos();
	ClearBubble->On();
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
	GetFSM()->ChangeState(PlayerStateType::Idle);
}

//플레이어 애니메이션 끄기 & 뒤쪽 거품 끄기
void PlayerState_StageMove::ExitState()
{
	ClearBubble->Off();
}

