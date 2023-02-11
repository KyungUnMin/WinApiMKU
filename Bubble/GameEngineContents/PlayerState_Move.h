#pragma once
#include "PlayerStateBase.h"

class GameEngineRender;

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
	const float4 MoveSpeed = float4{ 400.f, 0.f };
	
	void ResourceLoad();
	void CreateAnimation(PlayerCharacterType _CharacterType);
};

