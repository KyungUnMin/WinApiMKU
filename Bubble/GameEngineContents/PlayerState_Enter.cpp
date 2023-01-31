#include "PlayerState_Enter.h"

PlayerState_Enter::PlayerState_Enter()
{

}

PlayerState_Enter::~PlayerState_Enter()
{

}

void PlayerState_Enter::Start(PlayerCharacterType _CharacterType)
{
	//딱 한번만 리소스 로드
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		/*ResourceLoad("Left_PlayerMove.bmp", 5, 4);
		ResourceLoad("Right_PlayerMove.bmp", 5, 4);*/
		IsLoad = true;
	}


}

void PlayerState_Enter::Update(float _DeltaTime)
{

}
