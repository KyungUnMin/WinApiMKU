#pragma once
#include <string>
#include <string_view>
#include <GameEngineBase/GameEngineMath.h>
#include "ContentsEnum.h"

class PlayerState;
class PlayerBase;
class GameEngineRender;

class PlayerStateBase
{
public:
	PlayerStateBase();
	virtual ~PlayerStateBase() = 0;

	PlayerStateBase(const PlayerStateBase& _Other) = delete;
	PlayerStateBase(PlayerStateBase&& _Other) noexcept = delete;
	PlayerStateBase& operator=(const PlayerStateBase& _Other) = delete;
	PlayerStateBase& operator=(const PlayerStateBase&& _Other) noexcept = delete;

	PlayerState* GetOwner();

	inline void SetOwner(PlayerState* _Owner)
	{
		Owner = _Owner;
	}


	PlayerBase* GetPlayer();

	inline void SetPlayer(PlayerBase* _Player)
	{
		Player = _Player;
	}

	virtual void Start(PlayerCharacterType _CharacterType) = 0;
	virtual void EnterState();
	virtual void Update(float _DeltaTime) = 0;
	virtual void ExitState();

protected:
	void InitState(const std::string_view& _AniName);

	void ResourceLoad(const std::string_view& _ImageName, int _CutX, int _CutY);

	inline const std::string& GetAniName()
	{
		return AniName;
	}

	inline GameEngineRender* GetRender()
	{
		return Render;
	}

private:
	PlayerState*				Owner				= nullptr;
	PlayerBase*					Player				= nullptr;

	std::string					AniName			= "";
	GameEngineRender*	Render				= nullptr;

	const float4				PlayerScale		= float4{ 200.f, 200.f };

};

