#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineImage;

class Player : public GameEngineActor
{
public:
	Player();
	~Player();

	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(const Player&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRender* Render1 = nullptr;
	GameEngineRender* Render2 = nullptr;
};

