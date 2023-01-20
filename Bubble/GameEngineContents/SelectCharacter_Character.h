#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;

class SelectCharacter_Character : public GameEngineActor
{
public:
	enum class CharacterType
	{
		BUBBLUN,
		BOBBLUN,
		KULULUN,
		CORORON,
	};

	SelectCharacter_Character();
	~SelectCharacter_Character();

	SelectCharacter_Character(const SelectCharacter_Character& _Other) = delete;
	SelectCharacter_Character(SelectCharacter_Character&& _Other) noexcept = delete;
	SelectCharacter_Character& operator=(const SelectCharacter_Character& _Other) = delete;
	SelectCharacter_Character& operator=(const SelectCharacter_Character&& _Other) noexcept = delete;

	void SetCharacterType(CharacterType _Type);
	void Select();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRender*	CharRender		= nullptr;
	GameEngineRender*	NoticeRender	= nullptr;
	GameEngineRender*	NameRender	= nullptr;
	GameEngineRender*	ClearBubble		= nullptr;

	const float MaxBubbleScale		= 200.f;
	const float BubbleGrowValue	= 300.f;
};

