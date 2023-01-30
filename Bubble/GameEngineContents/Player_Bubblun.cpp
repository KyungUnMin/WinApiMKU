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
	//�÷��̾ ����� ������Ʈ�� �����ϰ� �ʱ�ȭ
	PlayerBase::Start();

	//PlayerState ������Ʈ�� BUBBLUN ĳ���� Ÿ������ �ʱ�ȭ
	PlayerState* State = GetComponent<PlayerState>(ComponentType::PlayerState);
	State->Init(PlayerCharacterType::BUBBLUN);
}
