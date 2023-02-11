#include "Gravity.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineActor.h>
#include "RoundLevelBase.h"
#include "MovableActor.h"
#include "BubbleCore.h"

Gravity::Gravity()
{

}

Gravity::~Gravity()
{
	
}


void Gravity::Start(GameEngineActor* _Owner, const float4& _CollisionScale)
{
	Owner = _Owner;
	CollisionScale = _CollisionScale;

	GameEngineLevel* Level = Owner->GetLevel();
	RoundLevel = dynamic_cast<RoundLevelBase*>(Level);
	if (nullptr == RoundLevel)
	{
		MsgAssert("현재 레벨은 RoundLevelBase를 상속받지 않았습니다");
	}
}

void Gravity::Update(float _DeltaTime)
{
	if (false == UseGravity)
		return;

	//현재위치
	float4 NowPos = Owner->GetPos();
	
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
		//충돌체보다 살짝 작은 가로 범위(바로 아래)
		float4 LeftCheckPos = (NowPos + float4::Left * CollisionScale.half()) + float4::Down + float4::Right;
		float4 RightCheckPos = (NowPos + float4::Right * CollisionScale.half()) + float4::Down + float4::Left;

		//아래로 떨어지는 경우(가속도 값이 양수)면서 내 바로 밑이 바닥일때
		if (0.f <= NowGravityAcc && (RoundLevel->IsBlockPos(LeftCheckPos) || RoundLevel->IsBlockPos(RightCheckPos)))
		{
			//가속도 0
			NowGravityAcc = 0.f;

			//가속도가 너무 빨라서 플레이어가 땅에 쳐박혔을때 위로 꺼내는 작업
			while (RoundLevel->IsBlockPos(NowPos))
			{
				//땅이 아닐때 까지 위로 올린다
				NowPos += float4::Up;
			}

			Owner->SetPos(NowPos);
			return;
		}
	}

	
	PrevGravityAcc = NowGravityAcc;

	//중력 가속도 더하기
	NowGravityAcc += GravityCoef * _DeltaTime;

	//중력가속도에 따른 값만큼 이동(float4::Down을 Up으로 바꾸면 계산이 덜 복잡할 것 같다)
	Owner->SetMove(float4::Down * NowGravityAcc * _DeltaTime);
}

void Gravity::DebugRender()
{
	if (false == BubbleCore::GetInst().IsDebug())
		return;

	GameEngineLevel::DebugTextPush(std::to_string(NowGravityAcc));
}

void Gravity::On()
{
	UseGravity = true;
}

void Gravity::Off()
{
	UseGravity = false;
	NowGravityAcc = 0.0f;
	PrevGravityAcc = 0.0f;
	IsTouchCollision = false;
}
