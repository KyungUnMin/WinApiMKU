#pragma once
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;

//SelectCharacter�������� ���Ǵ� ĳ����
class SelectCharacter_Character : public GameEngineActor
{
public:
	SelectCharacter_Character();
	~SelectCharacter_Character();

	SelectCharacter_Character(const SelectCharacter_Character& _Other) = delete;
	SelectCharacter_Character(SelectCharacter_Character&& _Other) noexcept = delete;
	SelectCharacter_Character& operator=(const SelectCharacter_Character& _Other) = delete;
	SelectCharacter_Character& operator=(const SelectCharacter_Character&& _Other) noexcept = delete;

	//�ش� ĳ���� Ÿ�� ĳ���� �ִϸ��̼� ����(�ܺο��� ȣ���ؾ� ��)
	void SetCharacterType(PlayerCharacterType _Type);

	//ĳ���� ���õǾ����� �ִϸ��̼� ��ȯ
	void Select();

	//ĳ���� �ִϸ��̼� �ʱ�ȭ
	void Reset();

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

