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
	void Render(float _DeltaTime) override;

private:
	float AccTime = 0.0f;
	int NowFrame = 0;

	GameEngineImage* Image = nullptr;
};

