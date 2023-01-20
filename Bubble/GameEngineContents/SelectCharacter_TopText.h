#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;

class SelectCharacter_TopText : public GameEngineActor
{
public:
	SelectCharacter_TopText();
	~SelectCharacter_TopText();

	SelectCharacter_TopText(const SelectCharacter_TopText& _Other) = delete;
	SelectCharacter_TopText(SelectCharacter_TopText&& _Other) noexcept = delete;
	SelectCharacter_TopText& operator=(const SelectCharacter_TopText& _Other) = delete;
	SelectCharacter_TopText& operator=(const SelectCharacter_TopText&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const float		BubbleOffset[12];

	float							AccTime						= 0.f;
	int								NumberFrameIndex	= 9;
	GameEngineRender*	NumberRender			= nullptr;
};

