#include "PlayerState_Move.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerBase.h"
#include "ContentsDefine.h"
#include "PlayerFSM.h"
#include "RoundLevelBase.h"

const float PlayerState_Move::MoveSpeed = 400.f;

PlayerState_Move::PlayerState_Move()
{

}

PlayerState_Move::~PlayerState_Move()
{

}

void PlayerState_Move::Start(PlayerCharacterType _CharacterType)
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


void PlayerState_Move::Update(float _DeltaTime)
{
	//���������� �̵��� ��
	if (true == GetRoundLevel()->IsMoving())
	{
		GetOwner()->ChangeState(PlayerStateType::StageMove);
		return;
	}

	//���߿� �ִ� ���
	float4 NowPos = GetPlayer()->GetPos();
	if (false == GetRoundLevel()->IsBlockPos(NowPos + float4::Down))
	{
		GetOwner()->ChangeState(PlayerStateType::Falling);
		return;
	}

	//�����ϴ� ���
	if (true == GameEngineInput::IsDown(PLAYER_JUMP))
	{
		GetOwner()->ChangeState(PlayerStateType::Jump);
		return;
	}

	//����Ű �� ���
	if (GameEngineInput::IsFree(PLAYER_LEFT) && GameEngineInput::IsFree(PLAYER_RIGHT))
	{
		GetOwner()->ChangeState(PlayerStateType::Idle);
		return;
	}

	
	//�÷��̾� ���� üũ
	PlayerStateBase::Update(_DeltaTime);

	//������ �̵��� ��ġ�� ���� �����ϴ��� Ȯ��
	float4 MoveDir = GetPlayer()->GetDirVec();
	if (true == GetRoundLevel()->IsBlockPos(NowPos + MoveDir * PlayerBase::CollisionScale * 0.5f))
		return;

	//���� �������� �ʴ´ٸ� �̵�
	GetPlayer()->SetMove(MoveDir * MoveSpeed * _DeltaTime);
}




void PlayerState_Move::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Player");
	Dir.Move("Move");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_PlayerMove.bmp"))->Cut(5, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_PlayerMove.bmp"))->Cut(5, 4);
}


void PlayerState_Move::CreateAnimation(PlayerCharacterType _CharacterType)
{
	int ImgXCnt = 5;
	int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

	SetAniName("Move");
	std::string LeftAniName = MovableActor::LeftStr + GetAniName();
	std::string RightAniName = MovableActor::RightStr + GetAniName();

	//���� �ִϸ��̼� ����
	GetRender()->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = "Left_PlayerMove.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.08f,
	});

	//������ �ִϸ��̼� ����
	GetRender()->CreateAnimation
	({
		.AnimationName = RightAniName,
		.ImageName = "Right_PlayerMove.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.08f,
	});
}

