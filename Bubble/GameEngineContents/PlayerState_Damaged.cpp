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

	//���� �ִϸ��̼� ����
	GetRender()->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = "Left_PlayerDamaged.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.1f,
		.Loop = false
		});

	//������ �ִϸ��̼� ����
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
	//�ִϸ��̼��� ���������� ���
	if (false == GetRender()->IsAnimationEnd())
		return;

	//�÷��̾� ������� ���ҽ�Ű�� �÷��̾ ����ִٸ�
	if (true == GetPlayer()->DecreaseLife())
	{
		GetFSM()->ChangeState(PlayerStateType::Idle);
		//GetPlayer()->SetPos(GetRoundLevel()->)
		return;
	}

	//�÷��̾ �׾�����
	GetPlayer()->Death();

	//TODO
	//GetRoundLevel()->
}
