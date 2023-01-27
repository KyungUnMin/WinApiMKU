#include "Gravity.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineActor.h>
#include "RoundLevelBase.h"

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
		MsgAssert("RoundLevel�� ���� ������ ����Ǿ� ���� �ʽ��ϴ�");
	}
}

void Gravity::Update(float _DeltaTime)
{
	float4 NowPos = GetOwner()->GetPos();
	float4 NextPos = NowPos + float4::Down;
	if (RoundLevel->IsBlockPos(NextPos))
	{
		Acceleration = 0.f;
		return;
	}

	Acceleration += GravityAcc * _DeltaTime;
	GetOwner()->SetMove(float4::Down * Acceleration * _DeltaTime);
}
