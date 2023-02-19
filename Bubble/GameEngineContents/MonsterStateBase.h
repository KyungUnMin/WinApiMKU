#pragma once
#include <string>
#include <string_view>
#include "MonsterBase.h"

class MonsterFSM;
class MonsterBase;
class FrameAnimationParameter;

typedef bool(MonsterBase::* StateChangeFuncPtr)(float);

class MonsterStateBase
{
public:
	friend MonsterFSM;

	MonsterStateBase();
	virtual ~MonsterStateBase() = 0;

	MonsterStateBase(const MonsterStateBase& _Other) = delete;
	MonsterStateBase(MonsterStateBase&& _Other) noexcept = delete;
	MonsterStateBase& operator=(const MonsterStateBase& _Other) = delete;
	MonsterStateBase& operator=(const MonsterStateBase&& _Other) noexcept = delete;

	void CreateAnimation(const FrameAnimationParameter& _Param);

	inline void SetStateChangeFunc(StateChangeFuncPtr _FuncPtr)
	{
		IsStateChange = _FuncPtr;
	}



protected:


	inline MonsterBase* GetMonster()
	{
		return Monster;
	}

	inline MonsterFSM* GetFSM()
	{
		return FsmPtr;
	}

	inline void SetNowAniName(const std::string_view& _AniName)
	{
		NowAniName = _AniName;
	}

	inline const std::string& GetNowAniName()
	{
		return NowAniName;
	}

	inline StateChangeFuncPtr GetStateChangeFunc()
	{
		return IsStateChange;
	}

	virtual void Start();
	virtual void Update(float _DeltaTime) {}
	virtual void Render(float _DeltaTime) {}

	virtual void EnterState();
	virtual void ExitState() {}

	float4 GetHorizonDirToPlayer();

	bool PlayerCollisionCheck();

	void ChangeAniDir();

private:
	StateChangeFuncPtr	IsStateChange		= nullptr;
	MonsterBase*				Monster				= nullptr;
	MonsterFSM*				FsmPtr					= nullptr;

	std::string					NowAniName;

	inline void SetMonster(MonsterBase* _Monster)
	{
		Monster = _Monster;
	}

	inline void SetFSM(MonsterFSM* _Fsm)
	{
		FsmPtr = _Fsm;
	}
};

