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
	//플레이어가 사용할 컴포넌트를 생성하고 초기화
	PlayerBase::Start();

	//PlayerState 컴포넌트를 KULULUN 캐릭터 타입으로 초기화
	PlayerState* State = GetComponent<PlayerState>(ComponentType::PlayerState);
	State->Init(PlayerCharacterType::KULULUN);
}
