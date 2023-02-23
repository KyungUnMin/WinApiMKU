#pragma once
#include "PlayerStateBase.h"

class PlayerState_Embarrassed : public PlayerStateBase
{
public:
	static const float Duration;

	PlayerState_Embarrassed();
	~PlayerState_Embarrassed() override;

	PlayerState_Embarrassed(const PlayerState_Embarrassed& _Other) = delete;
	PlayerState_Embarrassed(PlayerState_Embarrassed&& _Other) noexcept = delete;
	PlayerState_Embarrassed& operator=(const PlayerState_Embarrassed& _Other) = delete;
	PlayerState_Embarrassed& operator=(const PlayerState_Embarrassed&& _Other) noexcept = delete;

	void Start(PlayerCharacterType _CharacterType) override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

protected:

private:
	const std::string_view		AniName		= "Embarrassed";
	const std::string_view		ImagePath	= "Player_Embarrassed.bmp";
	float									AccTime		= 0.f;

	void ResourceLoad();
	void CreateAnimation(PlayerCharacterType _CharacterType);
};

