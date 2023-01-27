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

protected:
	void Init(PlayerCharacterType _CharacterType) override;
	void EnterState() override;
	void Update(float _DeltaTime) override;
	void ExitState() override;

private:
	GameEngineRender*	PlayerRender	= nullptr;
	RoundLevelBase*		RoundLevel		= nullptr;

	const float					MoveSpeed		= 250.f;
	const float					AirMoveSpeed	= 50.f;
	const float					ColliderScale	= 30.f;
};

