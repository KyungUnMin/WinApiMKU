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
	//플레이어 타입 설정
	SetCharacterType(PlayerCharacterType::KULULUN);

	//플레이어가 사용할 컴포넌트를 생성하고 초기화
	PlayerBase::Start();
}
