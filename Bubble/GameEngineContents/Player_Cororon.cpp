#include "Player_Cororon.h"
#include "ContentsEnum.h"


Player_Cororon::Player_Cororon()
{

}

Player_Cororon::~Player_Cororon()
{

}

void Player_Cororon::Start()
{
	//�÷��̾� Ÿ�� ����
	SetCharacterType(PlayerCharacterType::CORORON);

	//�÷��̾ ����� ������Ʈ�� �����ϰ� �ʱ�ȭ
	PlayerBase::Start();
}
