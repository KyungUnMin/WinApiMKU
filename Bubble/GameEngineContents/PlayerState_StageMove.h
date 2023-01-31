#pragma once
#include "PlayerStateBase.h"
#include "ContentsEnum.h"

class GameEngineRender;

class PlayerState_StageMove : public PlayerStateBase
{
public:
	PlayerState_StageMove();
	~PlayerState_StageMove() override;

	PlayerState_StageMove(const PlayerState_StageMove& _Other) = delete;
	PlayerState_StageMove(PlayerState_StageMove&& _Other) noexcept = delete;
	PlayerState_StageMove& operator=(const PlayerState_StageMove& _Other) = delete;
	PlayerState_StageMove& operator=(const PlayerState_StageMove&& _Other) noexcept = delete;

	void Start(PlayerCharacterType _CharacterType) override;
	void Update(float _DeltaTime) override;

	void EnterState() override;
	void ExitState() override;

protected:

private:
	GameEngineRender*		ClearBubble		= nullptr;

	void CreatePlayerAni(PlayerCharacterType _CharacterType);
	void CreateBubbleAni();
};

