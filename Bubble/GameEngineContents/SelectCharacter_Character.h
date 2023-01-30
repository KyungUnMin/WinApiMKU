#pragma once
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;

//SelectCharacter레벨에서 사용되는 캐릭터
class SelectCharacter_Character : public GameEngineActor
{
public:
	SelectCharacter_Character();
	~SelectCharacter_Character();

	SelectCharacter_Character(const SelectCharacter_Character& _Other) = delete;
	SelectCharacter_Character(SelectCharacter_Character&& _Other) noexcept = delete;
	SelectCharacter_Character& operator=(const SelectCharacter_Character& _Other) = delete;
	SelectCharacter_Character& operator=(const SelectCharacter_Character&& _Other) noexcept = delete;

	//해당 캐릭터 타입 캐릭터 애니메이션 생성(외부에서 호출해야 함)
	void SetCharacterType(PlayerCharacterType _Type);

	//캐릭터 선택되었을때 애니메이션 전환
	void Select();

	//캐릭터 애니메이션 초기화
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

