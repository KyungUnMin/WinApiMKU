#pragma once
#include "PlayerStateBase.h"

class GameEngineRender;
class RoundLevelBase;

class PlayerState_Move : public PlayerStateBase
{
public:
	PlayerState_Move();
	~PlayerState_Move() override;

	PlayerState_Move(const PlayerState_Move& _Other) = delete;
	PlayerState_Move(PlayerState_Move&& _Other) noexcept = delete;
	PlayerState_Move& operator=(const PlayerState_Move& _Other) = delete;
	PlayerState_Move& operator=(const PlayerState_Move&& _Other) noexcept = delete;

	void Start(PlayerCharacterType _CharacterType) override;
	void Update(float _DeltaTime) override;

protected:

private:
	RoundLevelBase*		RoundLevel		= nullptr;

	const float					MoveSpeed		= 250.f;
};

