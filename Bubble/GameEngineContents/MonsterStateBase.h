#pragma once
#include <string>
#include <string_view>

class MonsterFSM;
class MonsterBase;

class MonsterStateBase
{
public:
	MonsterStateBase();
	virtual ~MonsterStateBase() = 0;

	MonsterStateBase(const MonsterStateBase& _Other) = delete;
	MonsterStateBase(MonsterStateBase&& _Other) noexcept = delete;
	MonsterStateBase& operator=(const MonsterStateBase& _Other) = delete;
	MonsterStateBase& operator=(const MonsterStateBase&& _Other) noexcept = delete;

	virtual void Start() = 0;
	virtual void Update(float _DeltaTime) = 0;
	virtual void Render(float _DeltaTime) {}

	virtual void EnterState(){}
	virtual void ExitState(){}

	inline void SetMonster(MonsterBase* _Monster)
	{
		Monster = _Monster;
	}

	inline void SetFSM(MonsterFSM* _Fsm)
	{
		FsmPtr = _Fsm;
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

	inline const std::string_view& GetNowAniName()
	{
		return NowAniName;
	}

private:
	MonsterBase*		Monster		= nullptr;
	MonsterFSM*		FsmPtr			= nullptr;

	std::string			NowAniName;
};

