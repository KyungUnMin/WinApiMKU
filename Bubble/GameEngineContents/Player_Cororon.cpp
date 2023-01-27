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
	PlayerBase::Start();

	PlayerState* State = GetComponent<PlayerState>(ComponentType::PlayerState);
	State->Init(PlayerCharacterType::CORORON);
}
