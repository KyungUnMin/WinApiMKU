#include "Player_Bobblun.h"
#include "ContentsEnum.h"
#include "PlayerState.h"

Player_Bobblun::Player_Bobblun()
{

}

Player_Bobblun::~Player_Bobblun()
{

}

void Player_Bobblun::Start()
{
	//�÷��̾� Ÿ�� ����
	SetCharacterType(PlayerCharacterType::BOBBLUN);

	//�÷��̾ ����� ������Ʈ�� �����ϰ� �ʱ�ȭ
	PlayerBase::Start();
}
