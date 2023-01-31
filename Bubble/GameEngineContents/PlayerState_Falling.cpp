#include "PlayerState_Falling.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerBase.h"
#include "RoundLevelBase.h"
#include "PlayerState.h"
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
		ResourceLoad("Left_PlayerFalling.bmp", 2, 4);
		ResourceLoad("Right_PlayerFalling.bmp", 2, 4);
		IsLoad = true;
	}

	//���� Level�� ����
	PlayerStateBase::Start(_CharacterType);

	//�ִϸ��̼ǿ� Render ���� �� �̸� ����(���⼭ Renderũ�⵵ ����)
	SetAniRender("Falling");


	//ĳ���� Ÿ��
	int AniIndex = static_cast<int>(_CharacterType) * 2;

	//���� �ִϸ��̼� ����
	GetRender()->CreateAnimation
	({
		.AnimationName = "Left_Falling",
		.ImageName = "Left_PlayerFalling.bmp",
		.Start = AniIndex,
		.End = AniIndex + 1,
		.InterTimer = 0.25f,
	});

	//������ �ִϸ��̼� ����
	GetRender()->CreateAnimation
	({
		.AnimationName = "Right_Falling",
		.ImageName = "Right_PlayerFalling.bmp",
		.Start = AniIndex,
		.End = AniIndex + 1,
		.InterTimer = 0.25f,
	});

	//���� �޾ƿ���
	const std::string StartDir = GetPlayer()->GetDirStr();

	//���� ���⿡ ���� �ִϸ��̼� ��� ����
	GetRender()->ChangeAnimation(StartDir + GetAniName());

	//������ �� FSM���°� �ƴҼ� �ֱ� ������ ������ Off
	GetRender()->Off();
}


void PlayerState_Falling::Update(float _DeltaTime)
{
	//���������� �̵��� ��
	if (true == GetRoundLevel()->IsMoving())
	{
		GetOwner()->ChangeState(PlayerStateType::StageMove);
		return;
	}

	//�÷��̾��� ���� üũ
	PlayerStateBase::Update(_DeltaTime);
	float4 NowPos = GetPlayer()->GetPos();
	float4 MoveDir = GetPlayer()->GetDirVec();

	//�������鼭�� �̵��ϴ� ��쿡 �̵��� ��ġ�� ���� �ִ��� Ȯ��, ���ٸ� �̵�
	if (false == GetRoundLevel()->IsBlockPos(NowPos + MoveDir * MovableActor::ColliderRange))
	{
		GetPlayer()->SetMove(MoveDir * AirMoveSpeed * _DeltaTime);
	}

	//���߿� �ִ� ��쿣 return
	if (false == GetRoundLevel()->IsBlockPos(NowPos + float4::Down))
		return;

	//���� ���� ������ ����Ű�� �����ִ� ���
	if (true == GameEngineInput::IsPress(PlayerJump))
	{
		GetOwner()->ChangeState(PlayerStateType::Jump);
		return;
	}

	//�� �ܿ��� ���������� ���� ���� �����Ƿ� Idle
	GetOwner()->ChangeState(PlayerStateType::Idle);
}
