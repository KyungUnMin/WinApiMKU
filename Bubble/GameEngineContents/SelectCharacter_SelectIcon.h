#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;

//SelectCharacter레벨에서 사용되는 아이콘 클래스
class SelectCharacter_SelectIcon : public GameEngineActor
{
public:
	SelectCharacter_SelectIcon();
	~SelectCharacter_SelectIcon();

	SelectCharacter_SelectIcon(const SelectCharacter_SelectIcon& _Other) = delete;
	SelectCharacter_SelectIcon(SelectCharacter_SelectIcon&& _Other) noexcept = delete;
	SelectCharacter_SelectIcon& operator=(const SelectCharacter_SelectIcon& _Other) = delete;
	SelectCharacter_SelectIcon& operator=(const SelectCharacter_SelectIcon&& _Other) noexcept = delete;

	//현재 가르키고 있는 Index를 반환
	int GetCurIndex()
	{
		return CurIndex;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const float		UpOffset;

	int								CurIndex					= 0;
	GameEngineRender*	Render						= nullptr;

	void LoadSFX();
};

