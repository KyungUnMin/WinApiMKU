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
	//�� State�� ���� �ʱ�ȭ
	PlayerStateBase::Init(
		"Left_PlayerMove.bmp",
		"Right_PlayerMove.bmp",
		"Move",
		std::make_pair(5,4),
		0.08f);

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

