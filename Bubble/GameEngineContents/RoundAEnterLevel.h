#pragma once
#include "RoundLevelBase.h"

class NextDoor;

class RoundAEnterLevel : public RoundLevelBase
{
public:
	RoundAEnterLevel();
	~RoundAEnterLevel();

	RoundAEnterLevel(const RoundAEnterLevel& _Other) = delete;
	RoundAEnterLevel(RoundAEnterLevel&& _Other) noexcept = delete;
	RoundAEnterLevel& operator=(const RoundAEnterLevel& _Other) = delete;
	RoundAEnterLevel& operator=(const RoundAEnterLevel&& _Other) noexcept = delete;

	void Reset();

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;


private:
	NextDoor*	Door[3]				= { nullptr, nullptr, nullptr };
	int				SelectedDoor		= -1;
	float			NextLevelTime		= 3.f;


	void ResourceLoad();
	void CreateBackGround();
	void CreateDoor();
	void CreteaKey();
};

