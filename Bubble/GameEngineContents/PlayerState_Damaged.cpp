#include "PlayerState_Damaged.h"
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerBase.h"
#include "PlayerFSM.h"

PlayerState_Damaged::PlayerState_Damaged()
{

}

PlayerState_Damaged::~PlayerState_Damaged()
{

}

void PlayerState_Damaged::Start(PlayerCharacterType _CharacterType)
{
	//이 State의 정보 초기화
	PlayerStateBase::Init(
		"Left_PlayerDamaged.bmp",
		"Right_PlayerDamaged.bmp",
		"Damaged",
		std::make_pair(17, 4),
		0.1f, false);

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

void PlayerState_Damaged::Update(float _DeltaTime)
{
	//애니메이션이 끝날때까지 대기
	if (false == GetRender()->IsAnimationEnd())
		return;

	

	//플레이어 생명력을 감소시키고 플레이어가 살아있다면
	if (true == GetPlayer()->DecreaseLife())
	{
		GetOwner()->ChangeState(PlayerStateType::Idle);
		//GetPlayer()->SetPos(GetRoundLevel()->)
		return;
	}

	//플레이어가 죽었을때
	GetPlayer()->Death();

	//TODO
	//GetRoundLevel()->
}

