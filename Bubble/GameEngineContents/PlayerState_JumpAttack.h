#pragma once
#include "PlayerState_Jump.h"


class PlayerState_JumpAttack : public PlayerState_Jump
{
public:
	PlayerState_JumpAttack();
	~PlayerState_JumpAttack();

	PlayerState_JumpAttack(const PlayerState_JumpAttack& _Other) = delete;
	PlayerState_JumpAttack(PlayerState_JumpAttack&& _Other) noexcept = delete;
	PlayerState_JumpAttack& operator=(const PlayerState_JumpAttack& _Other) = delete;
	PlayerState_JumpAttack& operator=(const PlayerState_JumpAttack&& _Other) noexcept = delete;

	void Start(PlayerCharacterType _CharacterType) override;
	void Update(float _DeltaTime) override;
	

protected:

private:
	void ResourceLoad();
	void CreateAnimation(PlayerCharacterType _CharacterType);
};

