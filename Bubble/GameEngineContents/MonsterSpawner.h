#pragma once
#include <vector>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class GameEngineActor;

class MonsterSpawner
{
public:
	MonsterSpawner(GameEngineLevel* _Level);
	~MonsterSpawner();

	MonsterSpawner(const MonsterSpawner& _Other) = delete;
	MonsterSpawner(MonsterSpawner&& _Other) noexcept = delete;
	MonsterSpawner& operator=(const MonsterSpawner& _Other) = delete;
	MonsterSpawner& operator=(const MonsterSpawner&& _Other) noexcept = delete;

	inline void ReserveSpanwer(size_t _Count)
	{
		Monsters.reserve(_Count);
	}

	template <typename MonsterType>
	GameEngineActor* CreateMonsters(const float4& _Pos)
	{
		GameEngineActor* Monster = Level->CreateActor<MonsterType>(UpdateOrder::Monster);
		Monster->SetPos(_Pos);
		Monster->Off();
		Monsters.push_back(std::make_pair(Monster, _Pos));
		return Monster;
	}

	template <typename MonsterType>
	MonsterType* GetLastPushedMonster()
	{
		GameEngineActor* MonsterActor = Monsters.back().first;
		return dynamic_cast<MonsterType*>(MonsterActor);
	}

	bool IsAllMonsterOff();

	void AllMonsterOn();

	void AllMonsterOff();

protected:


private:
	GameEngineLevel*															Level = nullptr;
	std::vector<std::pair<GameEngineActor*, float4>>		Monsters;


};

