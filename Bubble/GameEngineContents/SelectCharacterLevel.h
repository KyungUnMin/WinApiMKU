#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <string>

class GameEngineRender;

enum class SelectCharacterRenderOrder
{
	BackGround,
	NoticeHandle,
	Character,
	Bubble,
	UI,
};

class SelectCharacter_Character;
class SelectCharacter_SelectIcon;

class SelectCharacterLevel : public GameEngineLevel
{
public:
	//TextLine의 위치
	static const float4					CharPos[4];
	static bool								Selected;

	int GetSelectCharacter();

	SelectCharacterLevel();
	~SelectCharacterLevel();

	SelectCharacterLevel(const SelectCharacterLevel& _Other) = delete;
	SelectCharacterLevel(SelectCharacterLevel&& _Other) noexcept = delete;
	SelectCharacterLevel& operator=(const SelectCharacterLevel& _Other) = delete;
	SelectCharacterLevel& operator=(const SelectCharacterLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override{}
	void LevelChangeStart(GameEngineLevel* _NextLevel) override{}

private:
	//TextLine을 통해 설명할 캐릭터 내용
	static const std::string			Description[5][4];

	float										SelectTime = 0.f;

	SelectCharacter_Character*	Characters[4]	= { nullptr, nullptr, nullptr, nullptr };
	SelectCharacter_SelectIcon* SelectIcon		= nullptr;

	void ResourceLoad();
	void CreateCharacters();
	void CreateDescriptionText();
};

