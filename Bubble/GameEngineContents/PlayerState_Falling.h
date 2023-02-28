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
	void EnterState() override;
	void ExitState() override;

protected:

private:
	const std::string_view	FallingAniName		= "Falling";
	const std::string_view	AttackAniName		= "Falling_Attack";

	const float4					AirMoveSpeed			= float4{ 100.f, 0.f };
	const float4					GravitySpeed			= float4{ 0.f, 300.f };
	const float						ScreenOutOffsetY	= 50.f;

	bool									IsBlocked				= false;

	void ResourceLoad();
	void CreateAnimation(PlayerCharacterType _CharacterType);

	bool CheckBubbleJump();
	bool CheckStateChange(float _DeltaTime);
	void Move(float _DeltaTime);
	void CheckAttack();
};



