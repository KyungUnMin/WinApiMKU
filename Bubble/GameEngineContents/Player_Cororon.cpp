#include "Player_Cororon.h"
#include "ContentsEnum.h"
#include "PlayerState.h"

Player_Cororon::Player_Cororon()
{

}

Player_Cororon::~Player_Cororon()
{

}

void Player_Cororon::Start()
{
	//�÷��̾ ����� ������Ʈ�� �����ϰ� �ʱ�ȭ
	PlayerBase::Start();

	//PlayerState ������Ʈ�� CORORON ĳ���� Ÿ������ �ʱ�ȭ
	PlayerState* State = GetComponent<PlayerState>(ComponentType::PlayerState);
	State->Init(PlayerCharacterType::CORORON);
}
