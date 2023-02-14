#include "PlayerState_Falling.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerBase.h"
#include "RoundLevelBase.h"
#include "PlayerFSM.h"
#include "ContentsDefine.h"


PlayerState_Falling::PlayerState_Falling()
{

}

PlayerState_Falling::~PlayerState_Falling()
{

}

void PlayerState_Falling::Start(PlayerCharacterType _CharacterType)
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



void PlayerState_Falling::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Player");
	Dir.Move("Falling");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_PlayerFalling.bmp"))->Cut(2, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_PlayerFalling.bmp"))->Cut(2, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_PlayerFalling_Attack.bmp"))->Cut(4, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_PlayerFalling_Attack.bmp"))->Cut(4, 4);
}

void PlayerState_Falling::CreateAnimation(PlayerCharacterType _CharacterType)
{
	//�Ϲ� �ִϸ��̼�
	{
		int ImgXCnt = 2;
		int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

		std::string LeftAniName = MovableActor::LeftStr + FallingAniName.data();
		std::string RightAniName = MovableActor::RightStr + FallingAniName.data();

		//���� �ִϸ��̼� ����
		GetRender()->CreateAnimation
		({
			.AnimationName = LeftAniName,
			.ImageName = "Left_PlayerFalling.bmp",
			.Start = AniIndex,
			.End = AniIndex + ImgXCnt - 1,
			.InterTimer = 0.25f,
		});

		//������ �ִϸ��̼� ����
		GetRender()->CreateAnimation
		({
			.AnimationName = RightAniName,
			.ImageName = "Right_PlayerFalling.bmp",
			.Start = AniIndex,
			.End = AniIndex + ImgXCnt - 1,
			.InterTimer = 0.25f,
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
			.ImageName = "Left_PlayerFalling_Attack.bmp",
			.Start = AniIndex,
			.End = AniIndex + ImgXCnt - 1,
			.InterTimer = 0.1f,
			.Loop = false
		});

		//������ �ִϸ��̼� ����
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

	SetNowAniName(FallingAniName);
}















void PlayerState_Falling::EnterState()
{
	PlayerStateBase::EnterState();

	//Falling���� ��ȯ������ �� ���ο� �����ߴ��� üũ
	IsBlocked = GetPlayer()->IsGround(PlayerBase::CollisionScale);
}






void PlayerState_Falling::Update(float _DeltaTime)
{
	//�ٸ� �ִϸ��̼����� ��ȯ�Ǵ� ���
	if (true == CheckStateChange(_DeltaTime))
		return;

	//������ ó��
	Move(_DeltaTime);

	CheckAttack();
}


bool PlayerState_Falling::CheckStateChange(float _DeltaTime)
{
	//���������� �̵��� ��
	if (true == GetRoundLevel()->IsMoving())
	{
		GetFSM()->ChangeState(PlayerStateType::StageMove);
		return true;
	}

	//Falling���°� �Ǿ����� �� �ȿ� �־���, ���� �� ���� �������Դٸ�
	if ((true == IsBlocked) && false == GetPlayer()->IsGround(PlayerBase::CollisionScale))
	{
		//�������� ���� ������� Idle���·� ��ȯ����
		IsBlocked = false;
	}

	//���� ��Ҵٸ� Idle���·� ��ȯ
	if (false == IsBlocked && true == GetPlayer()->IsGround(PlayerBase::CollisionScale))
	{
		GetFSM()->ChangeState(PlayerStateType::Idle);
		GetPlayer()->RaiseOnGround(PlayerBase::CollisionScale);
		return true;
	}

	return false;
}



void PlayerState_Falling::Move(float _DeltaTime)
{
	//�÷��̾��� ������ �ٲ�ٸ� �� ���⿡ ���� �ִϸ��̼� ��ȯ
	ChangeAniDir();

	//�Ʒ��� �̵�
	GetPlayer()->SetMove(float4::Down * GravitySpeed * _DeltaTime);

	//�������鼭�� �̵��Ҷ�
	if (GameEngineInput::IsPress(PLAYER_RIGHT) || GameEngineInput::IsPress(PLAYER_LEFT))
	{
		float4 ScreenSize = GameEngineWindow::GetScreenSize();
		float4 NowPos = GetPlayer()->GetPos();

		//ĳ���Ͱ� ȭ�� �Ʒ��� �������� �ʾ������� �����̱� ����
		if (NowPos.y < ScreenSize.y)
		{
			GetPlayer()->MoveHorizon(AirMoveSpeed.x, PlayerBase::CollisionScale, _DeltaTime);
		}
	}

	//ĳ���Ͱ� ȭ�� �Ʒ��� �������ٸ� ���� �ø���
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	float4 NowPos = GetPlayer()->GetPos();
	if (ScreenSize.y + ScreenOutOffsetY < NowPos.y)
	{
		//y�� 0���� �����
		GetPlayer()->SetPos(NowPos * float4::Right);
	}
}

void PlayerState_Falling::CheckAttack()
{
	//���� �ִϸ��̼��� ���� ���
	if (true == GetRender()->IsAnimationEnd())
	{
		GetRender()->ChangeAnimation(GetAniNamePlusDir(FallingAniName));
		SetNowAniName(FallingAniName);
	}

	//����Ű�� ���� ��츸
	if (false == GameEngineInput::IsDown(PLAYER_ATTACK))
		return;

	CreateBubble();
	GetRender()->ChangeAnimation(GetAniNamePlusDir(AttackAniName), true);
	SetNowAniName(AttackAniName);
}


void PlayerState_Falling::ExitState()
{
	SetNowAniName(FallingAniName);
}