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
	//�÷��̾ ����� ������Ʈ�� �����ϰ� �ʱ�ȭ
	PlayerBase::Start();

	//PlayerState ������Ʈ�� BOBBLUN ĳ���� Ÿ������ �ʱ�ȭ
	PlayerState* State = GetComponent<PlayerState>(ComponentType::PlayerState);
	State->Init(PlayerCharacterType::BOBBLUN);
}
