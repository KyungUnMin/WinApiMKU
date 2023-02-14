#pragma once
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class MonsterSpawnerBase
{
public:
	MonsterSpawnerBase(){}
	virtual ~MonsterSpawnerBase(){}

	virtual void CreateMonsters(const std::vector<float4>& _MonstersPos) = 0;
	virtual bool IsAllMonsterOff() = 0;
	virtual void Reset() = 0;
};


class GameEngineLevel;

template <typename MonsterType>
class MonsterSpawner : public MonsterSpawnerBase
{
public:
	MonsterSpawner(GameEngineLevel* _Level)
		:Level(_Level)
	{

	}
	~MonsterSpawner() override{}

	MonsterSpawner(const MonsterSpawner& _Other) = delete;
	MonsterSpawner(MonsterSpawner&& _Other) noexcept = delete;
	MonsterSpawner& operator=(const MonsterSpawner& _Other) = delete;
	MonsterSpawner& operator=(const MonsterSpawner&& _Other) noexcept = delete;

	void CreateMonsters(const std::vector<float4>& _MonstersPos) override
	{
		Monsters.reserve(_MonstersPos.size());

		for (float4 Pos : _MonstersPos)
		{
			GameEngineActor* Monster = Level->CreateActor<MonsterType>(UpdateOrder::Monster);
			Monster->SetPos(Pos);
			Monsters.push_back(std::make_pair(Monster, Pos));
		}
	}

	bool IsAllMonsterOff() override
	{
		for (std::pair<GameEngineActor*, float4> Pair : Monsters)
		{
			if (Pair.first->IsUpdate())
				return false;
		}

		return true;
	}

	void Reset() override
	{
		for (std::pair<GameEngineActor*, float4> Pair : Monsters)
		{
			GameEngineActor* Monster = Pair.first;
			float4 OriginPos = Pair.second;
			Monster->SetPos(OriginPos);
			Monster->On();
		}
	}

protected:


private:
	GameEngineLevel*														Level			= nullptr;
	std::vector<std::pair<GameEngineActor*, float4>>	Monsters;
};

