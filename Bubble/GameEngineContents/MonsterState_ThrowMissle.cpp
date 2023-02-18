#include "MonsterState_ThrowMissle.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "MonsterMissle_MightARock.h"
#include "MonsterBase.h"
#include "PlayerBase.h"
#include "MonsterFSM.h"

const float4 MonsterState_ThrowMissle::SpawnOffset = float4{ 0.f, -30.f };

MonsterState_ThrowMissle::MonsterState_ThrowMissle()
{

}

MonsterState_ThrowMissle::~MonsterState_ThrowMissle()
{

}

void MonsterState_ThrowMissle::Start()
{
	MonsterStateBase::Start();
	SetNowAniName("ThrowMissle");
	Monster = GetMonster();
}


void MonsterState_ThrowMissle::EnterState()
{
	MonsterStateBase::EnterState();

	if (MonMissleType::UNKNOWN == MissleType)
	{
		MsgAssert("MonsterMissleType을 지정해주지 않았습니다");
		return;
	}

	Missle = CreateMissle(MissleType);
	float4 CreatePos = Monster->GetPos();
	float4 Dir = Monster->GetDirVec();

	float4 MonsterColScale = MonsterBase::CollisionScale;
	float4 BubbleColScale = MonsterMissleBase::CollisionScale;

	CreatePos += Dir * (MonsterColScale.half() + BubbleColScale.half()) + SpawnOffset;
	Missle->SetPos(CreatePos);
}


MonsterMissleBase* MonsterState_ThrowMissle::CreateMissle(MonMissleType _Type)
{
	MonsterMissleBase* ReturnMissle = nullptr;
	GameEngineLevel* Level = Monster->GetLevel();

	switch (_Type)
	{
	case MonMissleType::MightARock:
		ReturnMissle = Level->CreateActor<MonsterMissle_MightARock>(UpdateOrder::Monster_Missle);
		break;

	default:
		MsgAssert("알 수 없는 MonsterMissleType입니다");
		break;
	}

	return ReturnMissle;
}



void MonsterState_ThrowMissle::Update(float _DeltaTime)
{
	//몬스터 객체에서 지정해준 우선 처리 사항
	StateChangeFuncPtr IsChangeState = GetStateChangeFunc();
	if (nullptr != IsChangeState)
	{
		if (true == (Monster->*IsChangeState)(_DeltaTime))
			return;
	}

	//애니메이션이 끝났다면 Move로 돌린다
	if (true == Monster->GetRender()->IsAnimationEnd())
	{
		GetFSM()->ChangeState(MonsterStateType::Move);
		return;
	}

	//플레이어와 충돌했을때
	if (true == PlayerCollisionCheck())
	{
		PlayerBase::MainPlayer->AttackPlayer();
		return;
	}
}



void MonsterState_ThrowMissle::ExitState()
{
	//Missle로 Throw 상태로 바꿔준다
	Missle->ThrowMissle(Monster->GetDirVec());
	Missle = nullptr;
}