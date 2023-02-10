#pragma once
#include "PlayerState_Move.h"


class PlayerState_MoveAttack : public PlayerState_Move
{
public:
	PlayerState_MoveAttack();
	~PlayerState_MoveAttack();

	PlayerState_MoveAttack(const PlayerState_MoveAttack& _Other) = delete;
	PlayerState_MoveAttack(PlayerState_MoveAttack&& _Other) noexcept = delete;
	PlayerState_MoveAttack& operator=(const PlayerState_MoveAttack& _Other) = delete;
	PlayerState_MoveAttack& operator=(const PlayerState_MoveAttack&& _Other) noexcept = delete;

	void Start(PlayerCharacterType _CharacterType) override;
	void Update(float _DeltaTime) override;

protected:

private:
	void ResourceLoad();
	void CreateAnimation(PlayerCharacterType _CharacterType);
};

