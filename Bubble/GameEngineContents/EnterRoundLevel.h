#pragma once
#include <string>
#include <GameEngineCore/GameEngineLevel.h>

enum class EnterRoundRenderOrder
{
	BackGround,
	Bubble,
	Player,
};

class EnterRoundCharater;
class GameEngineObject;

class EnterRoundLevel : public GameEngineLevel
{
public:
	EnterRoundLevel();
	~EnterRoundLevel();

	EnterRoundLevel(const EnterRoundLevel& _Other) = delete;
	EnterRoundLevel(EnterRoundLevel&& _Other) noexcept = delete;
	EnterRoundLevel& operator=(const EnterRoundLevel& _Other) = delete;
	EnterRoundLevel& operator=(const EnterRoundLevel&& _Other) noexcept = delete;



protected:
	void Loading() override;
	void Update(float _DeltaTime) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	GameEngineObject*			Bubbles		= nullptr;
	EnterRoundCharater*			Player			= nullptr;
	float									AccTime		= 0.f;

	static const std::string		TextString[3];
	static const float				TextHeight[3];


	void ResourceLoad();
	void CreateText();
};

