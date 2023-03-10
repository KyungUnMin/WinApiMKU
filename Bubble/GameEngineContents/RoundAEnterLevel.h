#pragma once
#include "RoundLevelBase.h"

class NextDoor;
class MonsterBase;
class MonsterSpawner;
class NavigationUI;

class RoundAEnterLevel : public RoundLevelBase
{
public:
	RoundAEnterLevel();
	~RoundAEnterLevel();

	RoundAEnterLevel(const RoundAEnterLevel& _Other) = delete;
	RoundAEnterLevel(RoundAEnterLevel&& _Other) noexcept = delete;
	RoundAEnterLevel& operator=(const RoundAEnterLevel& _Other) = delete;
	RoundAEnterLevel& operator=(const RoundAEnterLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	MonsterSpawner*	MonSpawner		= nullptr;
	NextDoor*				Door[3]				= { nullptr, nullptr, nullptr };
	int							SelectedDoor		= -1;
	float						NextLevelTime		= 3.f;

	bool							IsAllMonKill			= false;
	NavigationUI*			NaviUI					= nullptr;

	void ResourceLoad();
	void CreateBackGround();
	void CreateDoor();
	void CreateBubbleDest();
	void CreateMonsters();
	void Update_Cheet();
};

