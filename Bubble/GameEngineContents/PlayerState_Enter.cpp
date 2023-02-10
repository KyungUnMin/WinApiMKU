#include "PlayerState_Enter.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "MovableActor.h"

PlayerState_Enter::PlayerState_Enter()
{

}

PlayerState_Enter::~PlayerState_Enter()
{

}

void PlayerState_Enter::Start(PlayerCharacterType _CharacterType)
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

void PlayerState_Enter::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Player");
	Dir.Move("Enter");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_PlayerEnter.bmp"))->Cut(2, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_PlayerEnter.bmp"))->Cut(2, 4);
}

void PlayerState_Enter::CreateAnimation(PlayerCharacterType _CharacterType)
{
	int ImgXCnt = 2;
	int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

	SetAniName("Enter");
	std::string LeftAniName = MovableActor::LeftStr + GetAniName();
	std::string RightAniName = MovableActor::RightStr + GetAniName();

	//왼쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = "Left_PlayerEnter.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.5f,
		.Loop = false
	});

	//오른쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = RightAniName,
		.ImageName = "Right_PlayerEnter.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.5f,
		.Loop = false
	});
}
