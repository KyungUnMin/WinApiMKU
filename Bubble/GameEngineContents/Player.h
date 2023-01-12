#pragma once
#include <GameEngineCore/GameEngineActor.h>

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
	void Update() override;
	void Render() override;

private:

};

