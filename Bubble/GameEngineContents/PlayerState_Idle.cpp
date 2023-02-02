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
	//�� State�� ���� �ʱ�ȭ
	PlayerStateBase::Init(
		"Left_PlayerIdle.bmp",
		"Right_PlayerIdle.bmp",
		"Idle",
		std::make_pair(2, 4),
		0.25f);

	//�� �ѹ��� ���ҽ� �ε�
	static bool IsLoad = false;
	if (false== IsLoad)
	{
		PlayerStateBase::ResourceLoad();
		IsLoad = true;
	}

	//�ִϸ��̼� ���� �� RoundLevel�� ����
	PlayerStateBase::Start(_CharacterType);

	//�׽�Ʈ �ڵ�
	if (false == GameEngineInput::IsKey("Test_PlayerDamaged"))
		GameEngineInput::CreateKey("Test_PlayerDamaged", 'K');
}


void PlayerState_Idle::Update(float _DeltaTime)
{
	//�׽�Ʈ �ڵ�
	if (true == GameEngineInput::IsDown("Test_PlayerDamaged"))
	{
		GetOwner()->ChangeState(PlayerStateType::Damaged);
		return;
	}

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
	if (true == GameEngineInput::IsDown(PLAYER_JUMP))
	{
		GetOwner()->ChangeState(PlayerStateType::Jump);
		return;
	}

	//������ ���
	if(GameEngineInput::IsPress(PLAYER_LEFT) || GameEngineInput::IsPress(PLAYER_RIGHT))
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

