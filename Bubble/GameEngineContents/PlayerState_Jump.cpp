#include "PlayerState_Jump.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerState.h"
#include "PlayerBase.h"
#include "RoundLevelBase.h"
#include "ContentsDefine.h"

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
		ResourceLoad("Left_PlayerJump.bmp", 4, 4);
		ResourceLoad("Right_PlayerJump.bmp", 4, 4);
		IsLoad = true;
	}

	//���� Level�� ����
	PlayerStateBase::Start(_CharacterType);

	//�ִϸ��̼ǿ� Render ���� �� �̸� ����(���⼭ Renderũ�⵵ ����)
	SetAniRender("Jump");


	//ĳ���� Ÿ��
	int AniIndex = static_cast<int>(_CharacterType) * 4;

	//���� �ִϸ��̼� ����
	GetRender()->CreateAnimation
	({
		.AnimationName = "Left_Jump",
		.ImageName = "Left_PlayerJump.bmp",
		.Start = AniIndex,
		.End = AniIndex + 3,
		.InterTimer = 0.1f,
		.Loop = false
	});

	//������ �ִϸ��̼� ����
	GetRender()->CreateAnimation
	({
		.AnimationName = "Right_Jump",
		.ImageName = "Right_PlayerJump.bmp",
		.Start = AniIndex,
		.End = AniIndex + 3,
		.InterTimer = 0.1f,
		.Loop = false
	});

	//���� �޾ƿ���
	const std::string StartDir = GetPlayer()->GetDirStr();

	//���� ���⿡ ���� �ִϸ��̼� ��� ����
	GetRender()->ChangeAnimation(StartDir + GetAniName());

	//������ �� FSM���°� �ƴҼ� �ֱ� ������ ������ Off
	GetRender()->Off();
}

void PlayerState_Jump::Update(float _DeltaTime)
{
	//���������� �̵��� ��
	if (true == GetRoundLevel()->IsMoving())
	{
		GetOwner()->ChangeState(PlayerStateType::StageMove);
		return;
	}

	//������ġ�� �ְ����� �������
	if (0.f <= GetPlayer()->GetGravityAcc())
	{
		GetOwner()->ChangeState(PlayerStateType::Falling);
		return;
	}

	//�÷��̾� ���� üũ
	PlayerStateBase::Update(_DeltaTime);

	//�����߿��� �÷��̾ �̵�Ű�Ƕ�
	if (GameEngineInput::IsPress(PlayerRight) || GameEngineInput::IsPress(PlayerLeft))
	{
		float4 NowPos = GetPlayer()->GetPos();
		float4 MoveDir = GetPlayer()->GetDirVec();

		//�̵���Ű�� ��ġ�� ���� �ƴ϶�� �̵�
		if (false == GetRoundLevel()->IsBlockPos(NowPos + MoveDir * MovableActor::ColliderRange))
		{
			GetPlayer()->SetMove(MoveDir * AirMoveSpeed * _DeltaTime);
		}
	}
	
}

void PlayerState_Jump::EnterState()
{
	PlayerStateBase::EnterState();
	GetPlayer()->SetMove(float4::Up);
	GetPlayer()->SetGravityAcc(-JumpAcc);
}
