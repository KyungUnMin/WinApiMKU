#include "PlayerState_FallingAttack.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsDefine.h"
#include "RoundLevelBase.h"
#include "MovableActor.h"
#include "PlayerFSM.h"
#include "PlayerBase.h"


PlayerState_FallingAttack::PlayerState_FallingAttack()
{

}

PlayerState_FallingAttack::~PlayerState_FallingAttack()
{

}


void PlayerState_FallingAttack::Start(PlayerCharacterType _CharacterType)
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



void PlayerState_FallingAttack::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Player");
	Dir.Move("Attack");
	Dir.Move("Falling");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_PlayerFalling_Attack.bmp"))->Cut(4, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_PlayerFalling_Attack.bmp"))->Cut(4, 4);
}

void PlayerState_FallingAttack::CreateAnimation(PlayerCharacterType _CharacterType)
{
	int ImgXCnt = 4;
	int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

	SetAniName("Falling_Attack");
	std::string LeftAniName = MovableActor::LeftStr + GetAniName();
	std::string RightAniName = MovableActor::RightStr + GetAniName();

	//왼쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = "Left_PlayerFalling_Attack.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.1f,
		.Loop = false
	});

	//오른쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = RightAniName,
		.ImageName = "Right_PlayerFalling_Attack.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.1f,
		.Loop = false
	});
}







void PlayerState_FallingAttack::Update(float _DeltaTime)
{
	PlayerState_Falling::Update(_DeltaTime);
}