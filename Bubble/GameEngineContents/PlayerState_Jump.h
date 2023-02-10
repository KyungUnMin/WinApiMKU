#pragma once
#include "PlayerStateBase.h"

class RoundLevelBase;

class PlayerState_Jump : public PlayerStateBase
{
public:
	static const float					AirMoveSpeed;
	static const float					JumpAcc;

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
	

	void ResourceLoad();
	void CreateAnimation(PlayerCharacterType _CharacterType);
};

