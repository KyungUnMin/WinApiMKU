#pragma once
#include <string>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"

enum class EnterRoundRenderOrder
{
	BackGround,
	Bubble,
	PlayerBubble,
	Player,
};

class EnterRoundCharater;
class GameEngineObject;
class EnterRoundBubble;

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
	//���� ��ǰ ������
	EnterRoundBubble*			BubbleSpawner		= nullptr;

	//������ �÷��̾� Ÿ��
	PlayerCharacterType			SelectedCharater	= PlayerCharacterType::BUBBLUN;
	EnterRoundCharater*			Player						= nullptr;

	//�� ������ ����� �ð�
	float									AccTime					= 0.f;

	static const std::string		TextString[3];
	static const float				TextHeight[3];

	GameEngineSoundPlayer	SoundPlayer;
	const float							LevelChangeTime	= 8.5f;


	void ResourceLoad();
	void CreateText();
};

