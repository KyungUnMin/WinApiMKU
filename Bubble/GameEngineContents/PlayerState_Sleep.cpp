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
	//�� �ѹ��� ���ҽ� �ε�
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

	//���� �ִϸ��̼� ����
	GetRender()->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = "Left_PlayerSleep.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.25f,
		.Loop = AniLoop
		});

	//������ �ִϸ��̼� ����
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
	//�������� ��ȯ���϶�
	if (true == GetRoundLevel()->IsMoving())
	{
		GetFSM()->ChangeState(PlayerStateType::StageMove);
		return;
	}

	//����Ű�� ��������
	if (true == GameEngineInput::IsDown(PLAYER_JUMP))
	{
		GetFSM()->ChangeState(PlayerStateType::Jump);
		return;
	}

	//���� �Ǵ� ���������� �̵��Ϸ��� ������
	if (GameEngineInput::IsPress(PLAYER_RIGHT) || GameEngineInput::IsPress(PLAYER_LEFT))
	{
		GetFSM()->ChangeState(PlayerStateType::Move);
		return;
	}
}
