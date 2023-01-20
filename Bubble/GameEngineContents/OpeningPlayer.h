#pragma once
#include <GameEngineCore/GameEngineActor.h>

class OpeningPlayer : public GameEngineActor
{
public:
	OpeningPlayer();
	~OpeningPlayer();

	OpeningPlayer(const OpeningPlayer& _Other) = delete;
	OpeningPlayer(OpeningPlayer&& _Other) noexcept = delete;
	OpeningPlayer& operator=(const OpeningPlayer& _Other) = delete;
	OpeningPlayer& operator=(const OpeningPlayer&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

