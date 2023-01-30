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
	//플레이어가 사용할 컴포넌트를 생성하고 초기화
	PlayerBase::Start();

	//PlayerState 컴포넌트를 BOBBLUN 캐릭터 타입으로 초기화
	PlayerState* State = GetComponent<PlayerState>(ComponentType::PlayerState);
	State->Init(PlayerCharacterType::BOBBLUN);
}
