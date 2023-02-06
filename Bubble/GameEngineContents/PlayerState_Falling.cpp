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
	//�� State�� ���� �ʱ�ȭ
	PlayerStateBase::Init(
		"Left_PlayerFalling.bmp",
		"Right_PlayerFalling.bmp",
		"Falling",
		std::make_pair(2, 4),
		0.25f);

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

	//�������鼭�� �̵��ϴ� ��쿡 
	if (GameEngineInput::IsPress(PLAYER_RIGHT) || GameEngineInput::IsPress(PLAYER_LEFT))
	{
		//�̵��� ��ġ�� ���� �ִ��� Ȯ��, ���ٸ� �̵�
		if (false == GetRoundLevel()->IsBlockPos(NowPos + MoveDir * PlayerBase::CollisionScale * 0.5f))
		{
			GetPlayer()->SetMove(MoveDir * AirMoveSpeed * _DeltaTime);
		}
	}
	

	//���߿� �ִ� ��쿣 return
	if (false == GetRoundLevel()->IsBlockPos(NowPos + float4::Down))
		return;

	//���� ���� ������ ����Ű�� �����ִ� ���
	if (true == GameEngineInput::IsPress(PLAYER_JUMP))
	{
		GetOwner()->ChangeState(PlayerStateType::Jump);
		return;
	}

	////������ ��ġ�� ���϶� �� �Ʒ��� �̵�
	//while (GetRoundLevel()->IsBlockPos(NowPos))
	//{
	//	NowPos += float4::Down;
	//	GetPlayer()->SetPos(NowPos);
	//}

	//�� �ܿ��� ���������� ���� ���� �����Ƿ� Idle
	GetOwner()->ChangeState(PlayerStateType::Idle);
}
