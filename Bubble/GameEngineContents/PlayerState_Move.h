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
	void ExitState() override;

protected:

private:
	const std::string_view	MoveAniName		= "Move";
	const std::string_view	AttackAniName	= "Move_Attack";

	float4								MoveSpeed			= float4{ 300.f, 0.f };
	
	void ResourceLoad();
	void CreateAnimation(PlayerCharacterType _CharacterType);

	bool CheckStateChange(float _DeltaTime);
	void CheckAttack();
};

