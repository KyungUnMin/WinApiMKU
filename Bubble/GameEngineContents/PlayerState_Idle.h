#pragma once
#include "PlayerStateBase.h"

class GameEngineRender;

class PlayerState_Idle : public PlayerStateBase
{
public:
	PlayerState_Idle();
	~PlayerState_Idle() override;

	PlayerState_Idle(const PlayerState_Idle& _Other) = delete;
	PlayerState_Idle(PlayerState_Idle&& _Other) noexcept = delete;
	PlayerState_Idle& operator=(const PlayerState_Idle& _Other) = delete;
	PlayerState_Idle& operator=(const PlayerState_Idle&& _Other) noexcept = delete;

	void Start(PlayerCharacterType _CharacterType) override;
	void Update(float _DeltaTime) override;

protected:

private:

};

