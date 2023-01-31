#include "PlayerState_Move.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerBase.h"
#include "ContentsDefine.h"
#include "PlayerState.h"
#include "RoundLevelBase.h"

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
		ResourceLoad("Left_PlayerMove.bmp", 5, 4);
		ResourceLoad("Right_PlayerMove.bmp", 5, 4);
		IsLoad = true;
	}

	//���� Level�� ����
	PlayerStateBase::Start(_CharacterType);

	//�ִϸ��̼ǿ� Render ���� �� �̸� ����(���⼭ Renderũ�⵵ ����)
	SetAniRender("Move");

	//ĳ���� Ÿ��
	int AniIndex = static_cast<int>(_CharacterType) * 5;

	//���� �ִϸ��̼� ����
	GetRender()->CreateAnimation
	({
		.AnimationName = "Left_Move",
		.ImageName = "Left_PlayerMove.bmp",
		.Start = AniIndex,
		.End = AniIndex + 4,
		.InterTimer = AniInterval,
	});

	//������ �ִϸ��̼� ����
	GetRender()->CreateAnimation
	({
		.AnimationName = "Right_Move",
		.ImageName = "Right_PlayerMove.bmp",
		.Start = AniIndex,
		.End = AniIndex + 4,
		.InterTimer = AniInterval,
	});

	//���� �޾ƿ���
	const std::string StartDir = GetPlayer()->GetDirStr();

	//���� ���⿡ ���� �ִϸ��̼� ��� ����
	GetRender()->ChangeAnimation(StartDir + GetAniName());

	//������ �� FSM���°� �ƴҼ� �ֱ� ������ ������ Off
	GetRender()->Off();
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
	if (true == GameEngineInput::IsDown(PlayerJump))
	{
		GetOwner()->ChangeState(PlayerStateType::Jump);
		return;
	}

	//����Ű �� ���
	if (GameEngineInput::IsFree(PlayerLeft) && GameEngineInput::IsFree(PlayerRight))
	{
		GetOwner()->ChangeState(PlayerStateType::Idle);
		return;
	}

	
	//�÷��̾� ���� üũ
	PlayerStateBase::Update(_DeltaTime);

	//������ �̵��� ��ġ�� ���� �����ϴ��� Ȯ��
	float4 MoveDir = GetPlayer()->GetDirVec();
	if (true == GetRoundLevel()->IsBlockPos(NowPos + MoveDir * MovableActor::ColliderRange))
		return;

	//���� �������� �ʴ´ٸ� �̵�
	GetPlayer()->SetMove(MoveDir * MoveSpeed * _DeltaTime);
}

