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
	//플레이어 타입 설정
	SetCharacterType(PlayerCharacterType::BUBBLUN);

	//플레이어가 사용할 컴포넌트를 생성하고 초기화
	PlayerBase::Start();
}
