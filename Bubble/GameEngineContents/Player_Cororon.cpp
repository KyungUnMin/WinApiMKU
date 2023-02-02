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
	//플레이어 타입 설정
	SetCharacterType(PlayerCharacterType::CORORON);

	//플레이어가 사용할 컴포넌트를 생성하고 초기화
	PlayerBase::Start();
}
