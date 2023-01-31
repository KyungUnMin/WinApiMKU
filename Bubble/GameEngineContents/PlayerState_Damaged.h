#pragma once
#include "PlayerStateBase.h"

class PlayerState_Damaged : public PlayerStateBase
{
public:
	PlayerState_Damaged();
	~PlayerState_Damaged();

	PlayerState_Damaged(const PlayerState_Damaged& _Other) = delete;
	PlayerState_Damaged(PlayerState_Damaged&& _Other) noexcept = delete;
	PlayerState_Damaged& operator=(const PlayerState_Damaged& _Other) = delete;
	PlayerState_Damaged& operator=(const PlayerState_Damaged&& _Other) noexcept = delete;

	void Start(PlayerCharacterType _CharacterType) override;
	void Update(float _DeltaTime) override;

	void EnterState() override;

protected:

private:
	const int			ImgColCnt		= 17;
};

