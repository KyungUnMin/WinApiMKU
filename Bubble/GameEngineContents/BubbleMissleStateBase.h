#pragma once
#include <string>
#include <string_view>
#include <GameEngineBase/GameEngineMath.h>
#include "ContentsEnum.h"

class BubbleMissleFSM;
class BubbleMissle;

class BubbleMissleStateBase
{
	friend class BubbleMissleFSM;

public:
	BubbleMissleStateBase();
	virtual ~BubbleMissleStateBase() = 0;

	BubbleMissleStateBase(const BubbleMissleStateBase& _Other) = delete;
	BubbleMissleStateBase(BubbleMissleStateBase&& _Other) noexcept = delete;
	BubbleMissleStateBase& operator=(const BubbleMissleStateBase& _Other) = delete;
	BubbleMissleStateBase& operator=(const BubbleMissleStateBase&& _Other) noexcept = delete;

protected:
	virtual void Init(PlayerCharacterType _CharType, BubbleMissleType _BubbleType) = 0;
	virtual void Update(float _DeltaTime) = 0;
	virtual void EnterState();
	virtual void ExitState(){}

	inline BubbleMissleFSM* GetFSM()
	{
		return Fsm;
	}

	inline BubbleMissle* GetBubble()
	{
		return Bubble;
	}

	inline void SetAniName(const std::string_view& _Str)
	{
		AniName = _Str;
	}

	inline const std::string& GetAniName()
	{
		return AniName;
	}

	void PlayerCollisionCheck();

private:
	BubbleMissleFSM*		Fsm				= nullptr;
	BubbleMissle*				Bubble			= nullptr;

	std::string					AniName		= "";

	void BubbleChainPop();
};

