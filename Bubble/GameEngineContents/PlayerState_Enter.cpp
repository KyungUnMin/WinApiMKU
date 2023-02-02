#include "PlayerState_Enter.h"

PlayerState_Enter::PlayerState_Enter()
{

}

PlayerState_Enter::~PlayerState_Enter()
{

}

void PlayerState_Enter::Start(PlayerCharacterType _CharacterType)
{
	//�� State�� ���� �ʱ�ȭ
	PlayerStateBase::Init(
		"Left_PlayerEnter.bmp",
		"Right_PlayerEnter.bmp",
		"Enter",
		std::make_pair(2, 4),
		0.5f, false);

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

void PlayerState_Enter::Update(float _DeltaTime)
{

}
