#pragma once
#include "PlayerStateBase.h"

class RoundLevelBase;

class PlayerState_Jump : public PlayerStateBase
{
public:
	PlayerState_Jump();
	~PlayerState_Jump();

	PlayerState_Jump(const PlayerState_Jump& _Other) = delete;
	PlayerState_Jump(PlayerState_Jump&& _Other) noexcept = delete;
	PlayerState_Jump& operator=(const PlayerState_Jump& _Other) = delete;
	PlayerState_Jump& operator=(const PlayerState_Jump&& _Other) noexcept = delete;

	void Start(PlayerCharacterType _CharacterType) override;
	void Update(float _DeltaTime) override;

	void EnterState() override;

protected:

private:
	const float					AirMoveSpeed	= 250.f;
	const float					JumpAcc			= 400.f;

	void ResourceLoad();
	void CreateAnimation(PlayerCharacterType _CharacterType);
};

