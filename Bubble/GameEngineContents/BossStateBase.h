#pragma once
#include <string_view>
#include <GameEngineBase/GameEngineMath.h>
#include "ContentsEnum.h"

class BossMonsterFSM;
class BossMonster;

class BossStateBase
{
public:
	friend BossMonsterFSM;
	static bool IsSFXLoad;

	BossStateBase();
	virtual ~BossStateBase() = 0;

	BossStateBase(const BossStateBase& _Other) = delete;
	BossStateBase(BossStateBase&& _Other) noexcept = delete;
	BossStateBase& operator=(const BossStateBase& _Other) = delete;
	BossStateBase& operator=(const BossStateBase&& _Other) noexcept = delete;

protected:
	virtual void Start(){}
	virtual void Update(float _DeltaTime) = 0;
	virtual void Render(float _DeltaTime){}
	virtual void EnterState() = 0;
	virtual void ExitState(){}

	inline BossMonsterFSM* GetFSM()
	{
		return FsmPtr;
	}

	BossMonster* GetBoss();

	void ChangeAniDir(const std::string_view& _AniName);

	void CheckCollisionWithPlayer();

	int CheckCollisionWithNatureMissle();

	void DrawDebugArrow(const float4& _Start, const float4& _End);

private:
	BossMonsterFSM*	FsmPtr					= nullptr;

	inline void SetFSM(BossMonsterFSM* _FSM)
	{
		FsmPtr = _FSM;
	}

	void LoadSFX();
};

