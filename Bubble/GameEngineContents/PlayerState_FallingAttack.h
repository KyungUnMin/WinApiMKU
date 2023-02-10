#pragma once
#include "PlayerState_Falling.h"


class PlayerState_FallingAttack : public PlayerState_Falling
{
public:
	PlayerState_FallingAttack();
	~PlayerState_FallingAttack();

	PlayerState_FallingAttack(const PlayerState_FallingAttack& _Other) = delete;
	PlayerState_FallingAttack(PlayerState_FallingAttack&& _Other) noexcept = delete;
	PlayerState_FallingAttack& operator=(const PlayerState_FallingAttack& _Other) = delete;
	PlayerState_FallingAttack& operator=(const PlayerState_FallingAttack&& _Other) noexcept = delete;

	void Start(PlayerCharacterType _CharacterType) override;
	void Update(float _DeltaTime) override;

protected:

private:
	void ResourceLoad();
	void CreateAnimation(PlayerCharacterType _CharacterType);
};

