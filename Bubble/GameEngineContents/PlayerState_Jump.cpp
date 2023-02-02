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
	//�� State�� ���� �ʱ�ȭ
	PlayerStateBase::Init(
		"Left_PlayerJump.bmp",
		"Right_PlayerJump.bmp",
		"Jump",
		std::make_pair(4, 4));

	//�� �ѹ��� ���ҽ� �ε�
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		PlayerStateBase::ResourceLoad();
		IsLoad = true;
	}

	//�ִϸ��̼� ���� �� RoundLevel�� ����
	PlayerStateBase::Start(_CharacterType);
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
