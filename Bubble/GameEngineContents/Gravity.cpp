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
	//MovableActor가 동작하는 레벨인 RoundLevel 과 연결
	GameEngineLevel* Level = GetOwner()->GetLevel();
	RoundLevel = dynamic_cast<RoundLevelBase*>(Level);
	if (nullptr == RoundLevel)
	{
		MsgAssert("현재 레벨은 RoundLevelBase를 상속받지 않았습니다");
	}

	//MovableActor와 연결
	MovableOwner = dynamic_cast<MovableActor*>(GetOwner());
	if (nullptr == MovableOwner)
	{
		MsgAssert("이 컴포넌트를 가지고 있는 객체는 MovableActor를 상속받지 않았습니다");
	}
}

void Gravity::Update(float _DeltaTime)
{
	//현재 가속도 값 받아오기
	float NowGravityAcc = MovableOwner->GetGravityAcc();

	//현재위치
	float4 NowPos = GetOwner()->GetPos();
	//바로 아래 위치
	float4 DownPos = NowPos + float4::Down;

	//아래로 떨어지는 경우(가속도 값이 양수)
	if (0.f <= NowGravityAcc)
	{
		//내 바로 밑이 바닥일때만
		if (true == RoundLevel->IsBlockPos(DownPos))
		{
			//가속도 0
			MovableOwner->SetGravityAcc(0.f);

			//가속도가 너무 빨라서 플레이어가 땅에 쳐박혔을때 위로 꺼내는 작업
			while (RoundLevel->IsBlockPos(NowPos))
			{
				//땅이 아닐때 까지 위로 올린다
				NowPos += float4::Up;
			}

			GetOwner()->SetPos(NowPos);
			return;
		}
	}

	//위로 올라가는 경우, 점프하는 경우(가속도 값이 음수)
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
