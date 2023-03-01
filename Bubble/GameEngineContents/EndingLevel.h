#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>

class BackGround;

enum class EndingRenderOrder
{
	BackGround,
	BackCurtain,
	FrontCurtain,
};

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
	int										PlayerScore		= 0;
	BackGround*						BackImg			= nullptr;

	void LoadBGI();
	void LoadBGM();

	void ImageCreate();
};

