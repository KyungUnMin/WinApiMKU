#include "Player_Kululun.h"
#include "ContentsEnum.h"
#include "PlayerState.h"

Player_Kululun::Player_Kululun()
{

}

Player_Kululun::~Player_Kululun()
{

}

void Player_Kululun::Start()
{
	//�÷��̾ ����� ������Ʈ�� �����ϰ� �ʱ�ȭ
	PlayerBase::Start();

	//PlayerState ������Ʈ�� KULULUN ĳ���� Ÿ������ �ʱ�ȭ
	PlayerState* State = GetComponent<PlayerState>(ComponentType::PlayerState);
	State->Init(PlayerCharacterType::KULULUN);
}
