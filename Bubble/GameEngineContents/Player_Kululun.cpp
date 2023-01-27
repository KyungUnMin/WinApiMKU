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
	PlayerBase::Start();

	PlayerState* State = GetComponent<PlayerState>(ComponentType::PlayerState);
	State->Init(PlayerCharacterType::KULULUN);
}
