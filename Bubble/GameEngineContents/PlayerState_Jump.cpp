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
		LoadSFX();
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
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_PlayerJump_Attack.bmp"))->Cut(4, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_PlayerJump_Attack.bmp"))->Cut(4, 4);
}

void PlayerState_Jump::LoadSFX()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");
	Dir.Move("SFX");
	Dir.Move("Player");
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("PlayerJump.wav"));
}


void PlayerState_Jump::CreateAnimation(PlayerCharacterType _CharacterType)
{
	//�Ϲ� �ִϸ��̼�
	{
		int ImgXCnt = 4;
		int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

		std::string LeftAniName = MovableActor::LeftStr + JumpAniName.data();
		std::string RightAniName = MovableActor::RightStr + JumpAniName.data();

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


	//���� �ִϸ��̼�
	{
		int ImgXCnt = 4;
		int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

		std::string LeftAniName = MovableActor::LeftStr + AttackAniName.data();
		std::string RightAniName = MovableActor::RightStr + AttackAniName.data();

		//���� �ִϸ��̼� ����
		GetRender()->CreateAnimation
		({
			.AnimationName = LeftAniName,
			.ImageName = "Left_PlayerJump_Attack.bmp",
			.Start = AniIndex,
			.End = AniIndex + ImgXCnt - 1,
			.InterTimer = 0.1f,
			.Loop = false
		});

		//������ �ִϸ��̼� ����
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

	SetNowAniName(JumpAniName);
}










void PlayerState_Jump::EnterState()
{
	PlayerStateBase::EnterState();
	GameEngineResources::GetInst().SoundPlay("PlayerJump.wav");
	AccTime = 0.0f;
}



void PlayerState_Jump::Update(float _DeltaTime)
{
	//�÷��̾��� ������ �ٲ�ٸ� �� ���⿡ ���� �ִϸ��̼� ��ȯ
	ChangeAniDir();

	//�ð� ����
	AccTime += _DeltaTime;

	if (true == CheckStateChange(_DeltaTime))
		return;

	CheckAttack();
}



bool PlayerState_Jump::CheckStateChange(float _DeltaTime)
{
	//���������� �̵��� ��
	if (true == GetRoundLevel()->IsMoving())
	{
		GetFSM()->ChangeState(PlayerStateType::StageMove);
		return true;
	}

	//���� ���� �ð��� ���� ��������
	if (FallingChangeTime < AccTime)
	{
		GetFSM()->ChangeState(PlayerStateType::Falling);
		return true;
	}

	//�����̴ٰ� ������ ���ϴ� ��Ȳ�϶�
	if (false == Movement(_DeltaTime))
	{
		GetFSM()->ChangeState(PlayerStateType::Falling);
		return true;
	}

	return false;
}




bool PlayerState_Jump::Movement(float _DeltaTime)
{
	float Ratio = AccTime / FallingChangeTime;
	float4 NowJumpSpeed = float4::LerpClamp(JumpSpeed, float4::Zero, Ratio);

	float4 NowPos = GetPlayer()->GetPos();
	float4 NextPos = NowPos + (float4::Up * NowJumpSpeed * _DeltaTime);
	float4 CollisionScale = PlayerBase::CollisionScale;
	float PlayerHeight = CollisionScale.Size();

	//������ �̵��� ��ġ�� ��ũ���� �Ѿ�ٸ�
	/*if (NextPos.y - PlayerHeight < ScreenTopOffset)
		return false;*/

	GetPlayer()->SetPos(NextPos);


	//�����߿��� �÷��̾ �̵�Ű�Ƕ�
	if (GameEngineInput::IsPress(PLAYER_RIGHT) || GameEngineInput::IsPress(PLAYER_LEFT))
	{
		//������ ��� MoveHorizon�ȿ� ���� �پ������ �ִ� ������ �Լ��� �����ε��ϸ�
		//�߰��� �ɸ��� ������ ���ټ� ������ ����.(���Ŀ� �����غ���)
		GetPlayer()->MoveHorizon(AirMoveSpeed.x, PlayerBase::CollisionScale, _DeltaTime);
	}

	return true;
}



void PlayerState_Jump::CheckAttack()
{
	//���� �ִϸ��̼��� ���� ���
	if (true == GetRender()->IsAnimationEnd())
	{
		GetRender()->ChangeAnimation(GetAniNamePlusDir(JumpAniName));
		SetNowAniName(JumpAniName);
	}

	//����Ű�� ���� ��츸
	if (false == GameEngineInput::IsDown(PLAYER_ATTACK))
		return;

	CreateBubble();
	GetRender()->ChangeAnimation(GetAniNamePlusDir(AttackAniName), true);
	SetNowAniName(AttackAniName);
}

void PlayerState_Jump::ExitState()
{
	SetNowAniName(JumpAniName);
}
