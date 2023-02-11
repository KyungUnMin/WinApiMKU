#include "PlayerState_Sleep.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include "PlayerBase.h"
#include "ContentsDefine.h"
#include "PlayerFSM.h"
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
		ResourceLoad();
		IsLoad = true;
	}

	ConnectRoundLevel();
	CreateAnimation(_CharacterType);
}


void PlayerState_Sleep::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Player");
	Dir.Move("Sleep");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_PlayerSleep.bmp"))->Cut(3, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_PlayerSleep.bmp"))->Cut(3, 4);
}





void PlayerState_Sleep::CreateAnimation(PlayerCharacterType _CharacterType)
{
	bool AniLoop = true;
	if (_CharacterType == PlayerCharacterType::CORORON || _CharacterType == PlayerCharacterType::KULULUN)
	{
		AniLoop = false;
	}


	int ImgXCnt = 3;
	int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

	SetNowAniName("Sleep");
	std::string LeftAniName = MovableActor::LeftStr + GetNowAniName();
	std::string RightAniName = MovableActor::RightStr + GetNowAniName();

	//왼쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = "Left_PlayerSleep.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.25f,
		.Loop = AniLoop
		});

	//오른쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = RightAniName,
		.ImageName = "Right_PlayerSleep.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.25f,
		});
}


void PlayerState_Sleep::Update(float _DeltaTime)
{
	//스테이지 전환중일때
	if (true == GetRoundLevel()->IsMoving())
	{
		GetFSM()->ChangeState(PlayerStateType::StageMove);
		return;
	}

	//점프키를 눌렀을때
	if (true == GameEngineInput::IsDown(PLAYER_JUMP))
	{
		GetFSM()->ChangeState(PlayerStateType::Jump);
		return;
	}

	//왼쪽 또는 오른쪽으로 이동하려고 했을때
	if (GameEngineInput::IsPress(PLAYER_RIGHT) || GameEngineInput::IsPress(PLAYER_LEFT))
	{
		GetFSM()->ChangeState(PlayerStateType::Move);
		return;
	}
}
