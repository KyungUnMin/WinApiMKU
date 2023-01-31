#include "PlayerState_Idle.h"
#include <vector>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsDefine.h"
#include "ContentsEnum.h"
#include "PlayerState.h"
#include "PlayerBase.h"
#include "RoundLevelBase.h"


PlayerState_Idle::PlayerState_Idle()
{

}

PlayerState_Idle::~PlayerState_Idle()
{

}


void PlayerState_Idle::Start(PlayerCharacterType _CharacterType)
{
	//�� �ѹ��� ���ҽ� �ε�
	static bool IsLoad = false;
	if (false== IsLoad)
	{
		ResourceLoad("Left_PlayerIdle.bmp", 3, 4);
		ResourceLoad("Right_PlayerIdle.bmp", 3, 4);
		IsLoad = true;
	}

	//���� Level�� ����
	PlayerStateBase::Start(_CharacterType);

	//�ִϸ��̼ǿ� Render ���� �� �̸� ����(���⼭ Renderũ�⵵ ����)
	SetAniRender("Idle");

	//ĳ���� Ÿ��
	int AniIndex = static_cast<int>(_CharacterType) * 3;

	//���� �ִϸ��̼� ����
	GetRender()->CreateAnimation
	({
		.AnimationName = "Left_Idle",
		.ImageName = "Left_PlayerIdle.bmp",
		.Start = AniIndex,
		.End = AniIndex + 1,
		.InterTimer = 0.25f,
	});

	//������ �ִϸ��̼� ����
	GetRender()->CreateAnimation
	({
		.AnimationName = "Right_Idle",
		.ImageName = "Right_PlayerIdle.bmp",
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


void PlayerState_Idle::Update(float _DeltaTime)
{
	//���������� �̵��� ��
	if (true == GetRoundLevel()->IsMoving())
	{
		GetOwner()->ChangeState(PlayerStateType::StageMove);
		return;
	}

	//���߿� �ִ� ���
	if (false == GetRoundLevel()->IsBlockPos(GetPlayer()->GetPos() + float4::Down))
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

	//������ ���
	if(GameEngineInput::IsPress(PlayerLeft) || GameEngineInput::IsPress(PlayerRight))
	{
		GetOwner()->ChangeState(PlayerStateType::Move);
		return;
	}

	//idle ���°� ���� SleepChangeTime�ð���ŭ �귶����
	AccTime += _DeltaTime;
	if (SleepChangeTime < AccTime)
	{
		GetOwner()->ChangeState(PlayerStateType::Sleep);
		return;
	}

	//���⿡ ���� idle �ִϸ��̼� ����
	PlayerStateBase::Update(_DeltaTime);
}

