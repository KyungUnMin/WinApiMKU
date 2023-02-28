#include "Item_GravityNormal.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineDebug.h>
#include "RoundLevelBase.h"

Item_GravityNormal::Item_GravityNormal()
{

}

Item_GravityNormal::~Item_GravityNormal()
{

}

void Item_GravityNormal::Start()
{
	Item_Normal::Start();
	ConnectRoundLevel();

	const float4 MaxSpeed = float4{ 100.f, 450.f };
	NowSpeed.x = GameEngineRandom::MainRandom.RandomFloat(-MaxSpeed.x, MaxSpeed.x);
	NowSpeed.y = GameEngineRandom::MainRandom.RandomFloat(-MaxSpeed.y, -300.f);
}

void Item_GravityNormal::Update(float _DeltaTime)
{
	ItemBase::Update(_DeltaTime);
	if (true == IsDeath())
		return;

	if (true == IsLand)
		return;

	if ((0 < NowSpeed.y) && (RoundLevel->IsBlockPos(GetPos())))
	{
		IsLand = true;
		return;
	}
	
	NowSpeed += (float4::Down * GravityAcc * _DeltaTime);
	SetMove(NowSpeed * _DeltaTime);
}

void Item_GravityNormal::ConnectRoundLevel()
{
	RoundLevel = dynamic_cast<RoundLevelBase*>(GetLevel());
	if (nullptr == RoundLevel)
	{
		MsgAssert("아이템이 RoundLevel이 아닌곳에서 생성되었습니다");
		return;
	}
}
