#include "Gravity.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineActor.h>
#include "RoundLevelBase.h"
#include "MovableActor.h"

Gravity::Gravity()
{

}

Gravity::~Gravity()
{

}


void Gravity::Start()
{
	GameEngineLevel* Level = GetOwner()->GetLevel();
	RoundLevel = dynamic_cast<RoundLevelBase*>(Level);
	if (nullptr == RoundLevel)
	{
		MsgAssert("RoundLevel이 현재 레벨과 연결되어 있지 않습니다");
	}

	MovableOwner = dynamic_cast<MovableActor*>(GetOwner());
	if (nullptr == MovableOwner)
	{
		MsgAssert("이 컴포넌트를 가지고 있는 객체는 MovableActor를 상속받지 않았습니다");
	}
}

void Gravity::Update(float _DeltaTime)
{
	float4 NowPos = GetOwner()->GetPos();
	float4 NextPos = NowPos + float4::Down;
	if (true == RoundLevel->IsBlockPos(NextPos))
	{
		MovableOwner->SetGravityAcc(0.f);
		return;
	}

	MovableOwner->SetMoveGravityAcc(GravityCoef * _DeltaTime);
	GetOwner()->SetMove(float4::Down * MovableOwner->GetGravityAcc() * _DeltaTime);
}

//점프가 여기 있으면 안됨
//따로 PlayerState에서 만들어 줄것

//void Gravity::Jump(float _JumpAcc)
//{
//	float4 BelowPos = GetOwner()->GetPos() + float4::Down;
//
//	//공중에 있는 경우
//	if (false == RoundLevel->IsBlockPos(BelowPos))
//		return;
//
//	MovableOwner->SetGravityAcc(_JumpAcc);
//}