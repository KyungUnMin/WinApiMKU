#include "MonsterSpawner.h"
#include "MonsterBase.h"

MonsterSpawner::MonsterSpawner(GameEngineLevel* _Level)
	:Level(_Level)
{

}

MonsterSpawner::~MonsterSpawner()
{

}

bool MonsterSpawner::IsAllMonsterOff()
{
	for (auto Pair : Monsters)
	{
		if (Pair.first->IsUpdate())
			return false;
	}

	return true;
}

void MonsterSpawner::AllMonsterOn()
{
	for (auto Pair : Monsters)
	{
		GameEngineActor* Monster = Pair.first;
		float4 OriginPos = Pair.second;
		Monster->SetPos(OriginPos);
		Monster->On();
	}
}

void MonsterSpawner::AllMonsterOff()
{
	for (auto Pair : Monsters)
	{
		GameEngineActor* MonActor = Pair.first;
		MonsterBase* Monster = dynamic_cast<MonsterBase*>(MonActor);
		Monster->FSMReset();
		Monster->Off();
	}

}