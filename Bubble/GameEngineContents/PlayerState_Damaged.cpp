#include "PlayerState_Damaged.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include "PlayerBase.h"
#include "PlayerFSM.h"

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
		ResourceLoad();
		IsLoad = true;
	}

	ConnectRoundLevel();
	CreateAnimation(_CharacterType);
}



void PlayerState_Damaged::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Player");
	Dir.Move("Damaged");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_PlayerDamaged.bmp"))->Cut(17, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_PlayerDamaged.bmp"))->Cut(17, 4);
}



void PlayerState_Damaged::CreateAnimation(PlayerCharacterType _CharacterType)
{
	int ImgXCnt = 17;
	int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

	SetAniName("Damaged");
	std::string LeftAniName = MovableActor::LeftStr + GetAniName();
	std::string RightAniName = MovableActor::RightStr + GetAniName();

	//왼쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = "Left_PlayerDamaged.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.1f,
		.Loop = false
		});

	//오른쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = RightAniName,
		.ImageName = "Right_PlayerDamaged.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.1f,
		.Loop = false
		});
}





void PlayerState_Damaged::Update(float _DeltaTime)
{
	//애니메이션이 끝날때까지 대기
	if (false == GetRender()->IsAnimationEnd())
		return;

	//플레이어 생명력을 감소시키고 플레이어가 살아있다면
	if (true == GetPlayer()->DecreaseLife())
	{
		GetFSM()->ChangeState(PlayerStateType::Idle);
		//GetPlayer()->SetPos(GetRoundLevel()->)
		return;
	}

	//플레이어가 죽었을때
	GetPlayer()->Death();

	//TODO
	//GetRoundLevel()->
}
