#include "PlayerState_Enter.h"

PlayerState_Enter::PlayerState_Enter()
{

}

PlayerState_Enter::~PlayerState_Enter()
{

}

void PlayerState_Enter::Start(PlayerCharacterType _CharacterType)
{
	//이 State의 정보 초기화
	PlayerStateBase::Init(
		"Left_PlayerEnter.bmp",
		"Right_PlayerEnter.bmp",
		"Enter",
		std::make_pair(2, 4),
		0.5f, false);

	//딱 한번만 리소스 로드
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		PlayerStateBase::ResourceLoad();
		IsLoad = true;
	}

	//애니메이션 생성 및 RoundLevel과 연결
	PlayerStateBase::Start(_CharacterType);
}

void PlayerState_Enter::Update(float _DeltaTime)
{

}
