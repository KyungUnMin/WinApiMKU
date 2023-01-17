#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class TextLine;

class SelectPlayerLevel : public GameEngineLevel
{
public:
	SelectPlayerLevel();
	~SelectPlayerLevel();

	SelectPlayerLevel(const SelectPlayerLevel& _Other) = delete;
	SelectPlayerLevel(SelectPlayerLevel&& _Other) noexcept = delete;
	SelectPlayerLevel& operator=(const SelectPlayerLevel& _Other) = delete;
	SelectPlayerLevel& operator=(const SelectPlayerLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;

private:
	TextLine* Text = nullptr;

	float accTime = 0.0f;
};

