#include "PlayerState_Jump.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include "PlayerFSM.h"
#include "PlayerBase.h"
#include "RoundLevelBase.h"
#include "ContentsDefine.h"
#include "Gravity.h"

PlayerState_Jump::PlayerState_Jump()
{

}

PlayerState_Jump::~PlayerState_Jump()
{

}

void PlayerState_Jump::Start(PlayerCharacterType _CharacterType)
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




void PlayerState_Jump::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Player");
	Dir.Move("Jump");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_PlayerJump.bmp"))->Cut(4, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_PlayerJump.bmp"))->Cut(4, 4);
}


void PlayerState_Jump::CreateAnimation(PlayerCharacterType _CharacterType)
{
	int ImgXCnt = 4;
	int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

	SetAniName("Jump");
	std::string LeftAniName = MovableActor::LeftStr + GetAniName();
	std::string RightAniName = MovableActor::RightStr + GetAniName();

	//���� �ִϸ��̼� ����
	GetRender()->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = "Left_PlayerJump.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.1f,
		});

	//������ �ִϸ��̼� ����
	GetRender()->CreateAnimation
	({
		.AnimationName = RightAniName,
		.ImageName = "Right_PlayerJump.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.1f,
		});
}










void PlayerState_Jump::EnterState()
{
	PlayerStateBase::EnterState();
	AccTime = 0.0f;
}


void PlayerState_Jump::Update(float _DeltaTime)
{
	if (true == CheckStateChange(_DeltaTime))
		return;

	Move(_DeltaTime);
}



bool PlayerState_Jump::CheckStateChange(float _DeltaTime)
{
	//���������� �̵��� ��
	if (true == GetRoundLevel()->IsMoving())
	{
		GetFSM()->ChangeState(PlayerStateType::StageMove);
		return true;
	}

	//����Ű�� ������ ��
	if (true == GameEngineInput::IsDown(PLAYER_ATTACK))
	{
		//�̷��� JumpAttack�� �󸶳� ������ �����ؾ� ����???
		GetFSM()->ChangeState(PlayerStateType::JumpAttack);
		return true;
	}

	//�ð� ����
	AccTime += _DeltaTime;

	//���� ���� �ð��� ���� ��������
	if (FallingChangeTime < AccTime)
	{
		GetFSM()->ChangeState(PlayerStateType::Falling);
		return true;
	}

	return false;
}




void PlayerState_Jump::Move(float _DeltaTime)
{
	//�÷��̾��� ������ �ٲ�ٸ� �� ���⿡ ���� �ִϸ��̼� ��ȯ
	ChangeAniDir();

	float4 NowPos = GetPlayer()->GetPos();
	float4 NextPos = NowPos + (float4::Up * JumpSpeed * _DeltaTime);
	float4 CollisionScale = PlayerBase::CollisionScale;
	float PlayerHeight = CollisionScale.Size();

	//������ �̵��� ��ġ�� ��ũ���� �Ѿ�� ��������
	if (NextPos.y - PlayerHeight < ScreenTopOffset)
		return;

	GetPlayer()->SetPos(NextPos);


	//�����߿��� �÷��̾ �̵�Ű�Ƕ�
	if (GameEngineInput::IsPress(PLAYER_RIGHT) || GameEngineInput::IsPress(PLAYER_LEFT))
	{
		GetPlayer()->MoveHorizon(AirMoveSpeed.x, PlayerBase::CollisionScale, _DeltaTime);
	}
}
