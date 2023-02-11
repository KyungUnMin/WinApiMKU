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
	float				AccTime						= 0.0f;
	const float		FallingChangeTime		= 0.5f;

	const float4	AirMoveSpeed				= float4{ 250.f, 0.f };
	const float4	JumpSpeed					= float4{ 0.f, 600.f };
	const float		ScreenTopOffset		= 50.f;
	

	void ResourceLoad();
	void CreateAnimation(PlayerCharacterType _CharacterType);

	bool CheckStateChange(float _DeltaTime);
	void Move(float _DeltaTime);
};

