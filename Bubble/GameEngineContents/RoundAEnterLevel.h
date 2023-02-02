#pragma once
#include "RoundLevelBase.h"

class NextDoor;
class MonsterBase;


class RoundAEnterLevel : public RoundLevelBase
{
public:
	static const std::vector<float4> PlayerSpanwPos;
	static const float4						MonsterSpawnPos[3];


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
	NextDoor*	Door[3]				= { nullptr, nullptr, nullptr };
	int				SelectedDoor		= -1;
	float			NextLevelTime		= 3.f;


	std::vector<MonsterBase*> Monsters;

	void ResourceLoad();
	void CreateBackGround();
	void CreateDoor();
};

