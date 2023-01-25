#pragma once
#include <GameEngineCore/GameEngineLevel.h>

enum class RoundAEnter_RenderOrder
{
	Sky,
	BackGround,
	Door,
};

class NextDoor;

class RoundAEnterLevel : public GameEngineLevel
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
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;


private:
	NextDoor*	Door[3]				= { nullptr, nullptr, nullptr };
	int				SelectedDoor		= -1;
	float			NextLevelTime		= 3.f;

	void ResourceLoad();
	void CreateBackGround();
	void CreateDoor();
	void CreteaKey();
};
