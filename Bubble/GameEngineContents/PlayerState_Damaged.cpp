#include "PlayerState_Damaged.h"
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerBase.h"
#include "PlayerFSM.h"

PlayerState_Damaged::PlayerState_Damaged()
{

}

PlayerState_Damaged::~PlayerState_Damaged()
{

}

void PlayerState_Damaged::Start(PlayerCharacterType _CharacterType)
{
	//�� State�� ���� �ʱ�ȭ
	PlayerStateBase::Init(
		"Left_PlayerDamaged.bmp",
		"Right_PlayerDamaged.bmp",
		"Damaged",
		std::make_pair(17, 4),
		0.1f, false);

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

void PlayerState_Damaged::Update(float _DeltaTime)
{
	//�ִϸ��̼��� ���������� ���
	if (false == GetRender()->IsAnimationEnd())
		return;

	

	//�÷��̾� ������� ���ҽ�Ű�� �÷��̾ ����ִٸ�
	if (true == GetPlayer()->DecreaseLife())
	{
		GetOwner()->ChangeState(PlayerStateType::Idle);
		//GetPlayer()->SetPos(GetRoundLevel()->)
		return;
	}

	//�÷��̾ �׾�����
	GetPlayer()->Death();

	//TODO
	//GetRoundLevel()->
}

