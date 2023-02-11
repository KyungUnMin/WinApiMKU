#include "PlayerState_JumpAttack.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include "PlayerFSM.h"
#include "PlayerBase.h"
#include "RoundLevelBase.h"
#include "ContentsDefine.h"
#include "Gravity.h"

PlayerState_JumpAttack::PlayerState_JumpAttack()
{

}

PlayerState_JumpAttack::~PlayerState_JumpAttack()
{

}



void PlayerState_JumpAttack::Start(PlayerCharacterType _CharacterType)
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


void PlayerState_JumpAttack::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Player");
	Dir.Move("Attack");
	Dir.Move("Jump");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_PlayerJump_Attack.bmp"))->Cut(4, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_PlayerJump_Attack.bmp"))->Cut(4, 4);
}

void PlayerState_JumpAttack::CreateAnimation(PlayerCharacterType _CharacterType)
{
	int ImgXCnt = 4;
	int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

	SetAniName("Jump_Attack");
	std::string LeftAniName = MovableActor::LeftStr + GetAniName();
	std::string RightAniName = MovableActor::RightStr + GetAniName();

	//왼쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = "Left_PlayerJump_Attack.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.1f,
		.Loop = false
		});

	//오른쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = RightAniName,
		.ImageName = "Right_PlayerJump_Attack.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.1f,
		.Loop = false
	});
}





void PlayerState_JumpAttack::Update(float _DeltaTime)
{
	PlayerState_Jump::Update(_DeltaTime);
}





//Jump::EnterState가 호출되면 공중에서 한번 더 점프하게 된다
//그래서 override시킴
void PlayerState_JumpAttack::EnterState()
{
	PlayerStateBase::EnterState();
}
