#pragma once
#include <vector>
#include <string>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>

enum class OpeningRenderOrder
{
	BackGround,
	Monster,
	Curtain,
	Player,
	SpotLight,
	Logo
};

class GameEngineRender;
class GameEngineActor;

class OpeningLevel : public GameEngineLevel
{
public:
	OpeningLevel();
	~OpeningLevel();

	OpeningLevel(const OpeningLevel& _Other) = delete;
	OpeningLevel(OpeningLevel&& _Other) noexcept = delete;
	OpeningLevel& operator=(const OpeningLevel& _Other) = delete;
	OpeningLevel& operator=(const OpeningLevel&& _Other) noexcept = delete;


protected:
	void Loading() override;
	void Update(float _DeltaTime) override;

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override{}
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override {}

private:
	GameEngineSoundPlayer	SoundPlayer;
	float									AccTime				= 0.0f;

	GameEngineRender*			CompanyLogo		= nullptr;
	GameEngineRender*			BackCurtain			= nullptr;
	GameEngineRender*			GameLogo			= nullptr;

	GameEngineActor*				SpotLight			= nullptr;


	static const float				CompanyLogoOffTime;
	static const float				SpotLightOutTime;
	static const float				SpotLightStopTime;
	static const float				SpotLightOffTime;
	static const float				BackCurtainUpStartTime;
	static const float				GameLogoOnTime;
	static const float				NextLevelChangeTime;

	void ResourceLoad();
	void CreateBackGround();
	void CreateText();
	void SoundPlay();
};

