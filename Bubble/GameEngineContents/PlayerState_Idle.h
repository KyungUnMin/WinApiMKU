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
	void EnterState() override
	{
		PlayerStateBase::EnterState();
		AccTime = 0.f;
	}

protected:

private:
	float								AccTime					= 0.0f;
	const float						SleepChangeTime	= 3.f;
};

