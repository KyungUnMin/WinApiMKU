#pragma once
#include <vector>
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;

class EnterRoundBubble : public GameEngineActor
{
public:
	EnterRoundBubble();
	~EnterRoundBubble();

	EnterRoundBubble(const EnterRoundBubble& _Other) = delete;
	EnterRoundBubble(EnterRoundBubble&& _Other) noexcept = delete;
	EnterRoundBubble& operator=(const EnterRoundBubble& _Other) = delete;
	EnterRoundBubble& operator=(const EnterRoundBubble&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::vector<std::pair<float, GameEngineRender*>> Bubbles;
	float Dir[6] = { 0.f, };
	const float MoveSpeed = 100.f;
	const float RotateSpeed = 0.1f;
	const float BubbleSpawnTime = 2.f;

	float AccTime = 0.0f;

	void BubbleMove(float _DeltaTime);
	void BubbleCreate(float _DirRadian);
	
};

