#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;

//상단 텍스트이미지와 타이머가 존재하는 클래스
class SelectCharacter_TopText : public GameEngineActor
{
public:
	SelectCharacter_TopText();
	~SelectCharacter_TopText();

	SelectCharacter_TopText(const SelectCharacter_TopText& _Other) = delete;
	SelectCharacter_TopText(SelectCharacter_TopText&& _Other) noexcept = delete;
	SelectCharacter_TopText& operator=(const SelectCharacter_TopText& _Other) = delete;
	SelectCharacter_TopText& operator=(const SelectCharacter_TopText&& _Other) noexcept = delete;

	//타이머 초기화
	void Reset();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const float		BubbleOffset[12];

	float							AccTime						= 0.f;
	int								NumberFrameIndex	= 9;
	GameEngineRender*	NumberRender			= nullptr;
};

