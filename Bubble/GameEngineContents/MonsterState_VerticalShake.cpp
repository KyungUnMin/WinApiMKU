#include "MonsterState_VerticalShake.h"
#include "PlayerBase.h"
#include "MonsterFSM.h"

const std::string_view MonsterState_VerticalShake::AniName = "VerticalShake";

MonsterState_VerticalShake::MonsterState_VerticalShake()
{

}

MonsterState_VerticalShake::~MonsterState_VerticalShake()
{

}

void MonsterState_VerticalShake::Start()
{
	SetNowAniName(AniName);
}

void MonsterState_VerticalShake::EnterState()
{
	MonsterStateBase::EnterState();

	OriginPos = GetMonster()->GetPos();
	PivotPos = OriginPos + float4::Up * ShakeLength;
	MoveCnt = 0;
	AccTime = 0.f;
}



void MonsterState_VerticalShake::Update(float _DeltaTime)
{
	if (MoveCnt < (ShakeCnt * 2))
	{
		Move(_DeltaTime);
	}
	else
	{
		GetFSM()->ChangeState(MonsterStateType::Dizzy);
		return;
	}
}


void MonsterState_VerticalShake::Move(float _DeltaTime)
{
	//위로 이동하는 경우
	float4 StartPos = OriginPos;
	float4 DestPos = PivotPos;

	//아래로 이동하는 경우
	if (MoveCnt % 2)
	{
		StartPos = PivotPos;
		DestPos = OriginPos;;
	}

	AccTime += _DeltaTime;

	float Ratio = AccTime / MoveDuration;
	float4 NowPos = float4::LerpClamp(StartPos, DestPos, Ratio);
	GetMonster()->SetPos(NowPos);

	if (MoveDuration < AccTime)
	{
		AccTime -= MoveDuration;
		++MoveCnt;
	}
}