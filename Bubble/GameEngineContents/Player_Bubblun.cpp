#include "Player_Bubblun.h"
#include "ContentsEnum.h"
#include "PlayerState.h"

Player_Bubblun::Player_Bubblun()
{

}

Player_Bubblun::~Player_Bubblun()
{

}

void Player_Bubblun::Start()
{
	//�÷��̾� Ÿ�� ����
	SetCharacterType(PlayerCharacterType::BUBBLUN);

	//�÷��̾ ����� ������Ʈ�� �����ϰ� �ʱ�ȭ
	PlayerBase::Start();
}
