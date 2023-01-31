#pragma once
#include "PlayerStateBase.h"


class PlayerState_Sleep : public PlayerStateBase
{
public:
	PlayerState_Sleep();
	~PlayerState_Sleep();

	PlayerState_Sleep(const PlayerState_Sleep& _Other) = delete;
	PlayerState_Sleep(PlayerState_Sleep&& _Other) noexcept = delete;
	PlayerState_Sleep& operator=(const PlayerState_Sleep& _Other) = delete;
	PlayerState_Sleep& operator=(const PlayerState_Sleep&& _Other) noexcept = delete;

protected:
	void Start(PlayerCharacterType _CharacterType) override;
	void Update(float _DeltaTime) override;

private:
};

