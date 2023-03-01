#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>

class TextLine;

class EndingLevel : public GameEngineLevel
{
public:
	static const std::string_view BGIPath;

	EndingLevel();
	~EndingLevel() override;

	EndingLevel(const EndingLevel& _Other) = delete;
	EndingLevel(EndingLevel&& _Other) noexcept = delete;
	EndingLevel& operator=(const EndingLevel& _Other) = delete;
	EndingLevel& operator=(const EndingLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	GameEngineSoundPlayer	BgmCtrl;
	TextLine*								ScoreText = nullptr;

	void LoadBGI();
	void LoadBGM();

	void CreateText();
};

