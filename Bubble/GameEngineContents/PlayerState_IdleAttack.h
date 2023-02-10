#pragma once
#include "PlayerState_Idle.h"

class PlayerState_IdleAttack : public PlayerState_Idle
{
public:
	PlayerState_IdleAttack();
	~PlayerState_IdleAttack();

	PlayerState_IdleAttack(const PlayerState_IdleAttack& _Other) = delete;
	PlayerState_IdleAttack(PlayerState_IdleAttack&& _Other) noexcept = delete;
	PlayerState_IdleAttack& operator=(const PlayerState_IdleAttack& _Other) = delete;
	PlayerState_IdleAttack& operator=(const PlayerState_IdleAttack&& _Other) noexcept = delete;

	void Start(PlayerCharacterType _CharacterType) override;
	void Update(float _DeltaTime) override;

protected:

private:
	void ResourceLoad();
	void CreateAnimation(PlayerCharacterType _CharacterType);
};

