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
	float NowGravityAcc = MovableOwner->GetGravityAcc();

	float4 NowPos = GetOwner()->GetPos();
	float4 DownPos = NowPos + float4::Down;

	//아래로 떨어지는 경우(양수)
	if (0.f <= NowGravityAcc)
	{
		//내 바로 밑이 바닥이라면
		if (true == RoundLevel->IsBlockPos(DownPos))
		{
			//가속도 0
			MovableOwner->SetGravityAcc(0.f);
			return;
		}
	}

	//위로 올라가는 경우(음수)
	else
	{
		//내 바로 밑이 바닥이고 내 위치는 바닥이 아닐때만
		if (true == RoundLevel->IsBlockPos(DownPos) && false == RoundLevel->IsBlockPos(NowPos))
		{
			//가속도 0
			MovableOwner->SetGravityAcc(0.f);
			return;
		}
	}

	//중력 가속도 더하기
	MovableOwner->SetMoveGravityAcc(GravityCoef * _DeltaTime);

	//중력가속도에 따른 값만큼 이동(float4::Down을 Up으로 바꾸면 계산이 덜 복잡할 것 같다)
	GetOwner()->SetMove(float4::Down * NowGravityAcc * _DeltaTime);

	//여기서 땅에 파묻힌 경우 예외처리 해야 할 수 도 있음
}
