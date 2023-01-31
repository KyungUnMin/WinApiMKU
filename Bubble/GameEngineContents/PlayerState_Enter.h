#pragma once
#include "PlayerStateBase.h"

class PlayerState_Enter : public PlayerStateBase
{
public:
	PlayerState_Enter();
	~PlayerState_Enter();

	PlayerState_Enter(const PlayerState_Enter& _Other) = delete;
	PlayerState_Enter(PlayerState_Enter&& _Other) noexcept = delete;
	PlayerState_Enter& operator=(const PlayerState_Enter& _Other) = delete;
	PlayerState_Enter& operator=(const PlayerState_Enter&& _Other) noexcept = delete;

	void Start(PlayerCharacterType _CharacterType) override;
	void Update(float _DeltaTime) override;

protected:

private:

};

