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
	//�÷��̾� Ÿ�� ����
	SetCharacterType(PlayerCharacterType::KULULUN);

	//�÷��̾ ����� ������Ʈ�� �����ϰ� �ʱ�ȭ
	PlayerBase::Start();
}
