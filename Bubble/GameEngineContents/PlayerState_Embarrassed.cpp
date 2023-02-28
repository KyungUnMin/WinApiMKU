#include "PlayerState_Embarrassed.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerFSM.h"
#include "RoundLevelBase.h"

const float PlayerState_Embarrassed::Duration = 1.f;


PlayerState_Embarrassed::PlayerState_Embarrassed()
{

}

PlayerState_Embarrassed::~PlayerState_Embarrassed()
{

}

void PlayerState_Embarrassed::Start(PlayerCharacterType _CharacterType)
{
	ResourceLoad();
	ConnectRoundLevel();
	CreateAnimation(_CharacterType);
}


void PlayerState_Embarrassed::ResourceLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Player");
	Dir.Move("Embarrassed");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(ImagePath))->Cut(2, 4);
	IsLoad = true;
}

void PlayerState_Embarrassed::CreateAnimation(PlayerCharacterType _CharacterType)
{
	int ImgXCnt = 2;
	int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

	//애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = ImagePath,
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.25f,
	});
}




void PlayerState_Embarrassed::EnterState()
{
	GetRender()->ChangeAnimation(AniName, true);
	AccTime = 0.f;
}



void PlayerState_Embarrassed::Update(float _DeltaTime)
{
	//스테이지가 이동할 때
	if (true == GetRoundLevel()->IsMoving())
	{
		GetFSM()->ChangeState(PlayerStateType::StageMove);
		return;
	}
	
	AccTime += _DeltaTime;
	if (AccTime < Duration)
		return;

	GetFSM()->ChangeState(PlayerStateType::Idle);
}


