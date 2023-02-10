#pragma once
#include "PlayerStateBase.h"

class GameEngineRender;

class PlayerState_Move : public PlayerStateBase
{

public:
	static const float MoveSpeed;

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

	void ResourceLoad();
	void CreateAnimation(PlayerCharacterType _CharacterType);
};

