#pragma once
#include "PlayerStateBase.h"


class PlayerState_Falling : public PlayerStateBase
{
public:
	PlayerState_Falling();
	~PlayerState_Falling();

	PlayerState_Falling(const PlayerState_Falling& _Other) = delete;
	PlayerState_Falling(PlayerState_Falling&& _Other) noexcept = delete;
	PlayerState_Falling& operator=(const PlayerState_Falling& _Other) = delete;
	PlayerState_Falling& operator=(const PlayerState_Falling&& _Other) noexcept = delete;

	void Start(PlayerCharacterType _CharacterType) override;
	void Update(float _DeltaTime) override;

protected:

private:

};

