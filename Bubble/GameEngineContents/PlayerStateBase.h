#pragma once
#include <string>
#include <string_view>
#include <GameEngineBase/GameEngineMath.h>
#include "ContentsEnum.h"

class PlayerState;
class PlayerBase;

class PlayerStateBase
{
	friend PlayerState;

public:
	PlayerStateBase();
	virtual ~PlayerStateBase() = 0;

	PlayerStateBase(const PlayerStateBase& _Other) = delete;
	PlayerStateBase(PlayerStateBase&& _Other) noexcept = delete;
	PlayerStateBase& operator=(const PlayerStateBase& _Other) = delete;
	PlayerStateBase& operator=(const PlayerStateBase&& _Other) noexcept = delete;

	PlayerState* GetOwner();
	PlayerBase* GetPlayer();

protected:
	virtual void Init(PlayerCharacterType _CharacterType) = 0;
	virtual void EnterState() = 0;
	virtual void Update(float _DeltaTime) = 0;
	virtual void ExitState() = 0;

	void ResourceLoad(const std::string_view& _ImageName, int _CutX, int _CutY);

	const float4		PlayerScale = float4{ 200.f, 200.f };

private:
	PlayerState*		Owner	= nullptr;
	PlayerBase*			Player	= nullptr;
};

