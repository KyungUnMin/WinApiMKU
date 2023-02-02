#include "Gravity.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineActor.h>
#include "RoundLevelBase.h"
#include "MovableActor.h"

bool Gravity::GlobalGravityUse = true;

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
	if (false == GlobalGravityUse)
		return;

	//현재위치
	float4 NowPos = GetOwner()->GetPos();
	
	//현재 가속도 값 받아오기
	float NowGravityAcc = MovableOwner->GetGravityAcc();

	//점프하다가 아래로 내려오는 경우
	if (0.f < NowGravityAcc && PrevGravityAcc < 0.f)
	{
		//점프했을때 Stage에 닿은 경우
		if (true == RoundLevel->IsBlockPos(NowPos))
		{
			IsTouchCollision = true;
		}
		else
		{
			IsTouchCollision = false;
		}
	}

	//콜리전에서 빠져나온 경우
	if (true == IsTouchCollision && false == RoundLevel->IsBlockPos(NowPos))
	{
		IsTouchCollision = false;
	}

	if (false == IsTouchCollision)
	{
		//바로 아래 위치
		float4 DownPos = NowPos + float4::Down;

		//아래로 떨어지는 경우(가속도 값이 양수)면서 내 바로 밑이 바닥일때
		if (0.f <= NowGravityAcc && RoundLevel->IsBlockPos(DownPos))
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

	//중력 가속도 더하기
	MovableOwner->SetMoveGravityAcc(GravityCoef * _DeltaTime);

	//중력가속도에 따른 값만큼 이동(float4::Down을 Up으로 바꾸면 계산이 덜 복잡할 것 같다)
	GetOwner()->SetMove(float4::Down * NowGravityAcc * _DeltaTime);

	
	PrevGravityAcc = NowGravityAcc;
}
