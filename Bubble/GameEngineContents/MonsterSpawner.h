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
		Monsters.resize(_MonstersPos.size(), nullptr);

		for (float4 Pos : _MonstersPos)
		{
			MonsterType* Monster = Level->CreateActor<MonsterType>(UpdateOrder::Monster);
			GameEngineActor* MonsterActor = Monster;

			MonsterActor->SetPos(Pos);
			Monsters.push_back(Monster);
		}
	}

	bool IsAllMonsterOff() override
	{
		for (GameEngineActor* Monster : Monsters)
		{
			if (Monster->IsUpdate())
				return false;
		}

		return true;
	}

protected:


private:
	GameEngineLevel*							Level			= nullptr;
	std::vector<GameEngineActor*>	Monsters;
};

