#include "PlayerState_Falling.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerBase.h"
#include "RoundLevelBase.h"
#include "PlayerFSM.h"
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
		ResourceLoad();
		IsLoad = true;
	}

	ConnectRoundLevel();
	CreateAnimation(_CharacterType);
}



void PlayerState_Falling::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Player");
	Dir.Move("Falling");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_PlayerFalling.bmp"))->Cut(2, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_PlayerFalling.bmp"))->Cut(2, 4);
}

void PlayerState_Falling::CreateAnimation(PlayerCharacterType _CharacterType)
{
	int ImgXCnt = 2;
	int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

	SetAniName("Falling");
	std::string LeftAniName = MovableActor::LeftStr + GetAniName();
	std::string RightAniName = MovableActor::RightStr + GetAniName();

	//왼쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = "Left_PlayerFalling.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.25f,
	});

	//오른쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = RightAniName,
		.ImageName = "Right_PlayerFalling.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.25f,
	});
}







void PlayerState_Falling::EnterState()
{
	PlayerStateBase::EnterState();

	//Falling으로 전환됐을때 벽 내부에 존재했는지 체크
	IsBlocked = GetPlayer()->IsGround(PlayerBase::CollisionScale);
}




void PlayerState_Falling::Update(float _DeltaTime)
{
	//다른 애니메이션으로 전환되는 경우
	if (true == CheckStateChange(_DeltaTime))
		return;

	//움직임 처리
	Move(_DeltaTime);
}


bool PlayerState_Falling::CheckStateChange(float _DeltaTime)
{
	//스테이지가 이동할 때
	if (true == GetRoundLevel()->IsMoving())
	{
		GetFSM()->ChangeState(PlayerStateType::StageMove);
		return true;
	}

	//공격키를 누른 경우
	if (true == GameEngineInput::IsDown(PLAYER_ATTACK))
	{
		GetFSM()->ChangeState(PlayerStateType::FallingAttack);
		return true;
	}

	//Falling상태가 되었을때 벽 안에 있었고, 이젠 그 벽을 빠져나왔다면
	if ((true == IsBlocked) && false == GetPlayer()->IsGround(PlayerBase::CollisionScale))
	{
		//이제부터 땅에 닿았을때 Idle상태로 변환가능
		IsBlocked = false;
	}

	//땅에 닿았다면 Idle상태로 전환
	if (false == IsBlocked && true == GetPlayer()->IsGround(PlayerBase::CollisionScale))
	{
		GetFSM()->ChangeState(PlayerStateType::Idle);
		GetPlayer()->RaiseOnGround(PlayerBase::CollisionScale);
		return true;
	}

	return false;
}



void PlayerState_Falling::Move(float _DeltaTime)
{
	//플레이어의 방향이 바뀌였다면 그 방향에 따라 애니메이션 전환
	ChangeAniDir();

	//아래로 이동
	GetPlayer()->SetMove(float4::Down * GravitySpeed * _DeltaTime);

	//떨어지면서도 이동할때
	if (GameEngineInput::IsPress(PLAYER_RIGHT) || GameEngineInput::IsPress(PLAYER_LEFT))
	{
		float4 ScreenSize = GameEngineWindow::GetScreenSize();
		float4 NowPos = GetPlayer()->GetPos();

		//캐릭터가 화면 아래로 내려가지 않았을때만 움직이기 가능
		if (NowPos.y < ScreenSize.y)
		{
			GetPlayer()->MoveHorizon(AirMoveSpeed.x, PlayerBase::CollisionScale, _DeltaTime);
		}
	}

	//캐릭터가 화면 아래로 내려갔다면 위로 올리기
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	float4 NowPos = GetPlayer()->GetPos();
	if (ScreenSize.y + ScreenOutOffsetY < NowPos.y)
	{
		//y를 0으로 만들기
		GetPlayer()->SetPos(NowPos * float4::Right);
	}
}
