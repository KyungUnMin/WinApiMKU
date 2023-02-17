#pragma once
#include <map>

enum class MonsterStateType
{
	Falling,
	Move,
	Jump,
	Lock,
	Dead,

	NonStopDash,
	Tired,



};

class MonsterStateBase;
class MonsterBase;
class BubbleMissle;

class MonsterFSM
{
public:
	friend class MonsterBase;

	MonsterFSM(const MonsterFSM& _Other) = delete;
	MonsterFSM(MonsterFSM&& _Other) noexcept = delete;
	MonsterFSM& operator=(const MonsterFSM& _Other) = delete;
	MonsterFSM& operator=(const MonsterFSM&& _Other) noexcept = delete;

	template <typename StateType>
	StateType* CreateState(MonsterStateType _Type)
	{
		StateType* StetePtr = new StateType;
		States[_Type] = StetePtr;
		return StetePtr;
	}

	void ChangeState(MonsterStateType _NextState);

	MonsterStateType GetCurStateByEnum();

protected:
	

private:
	std::map<MonsterStateType, MonsterStateBase*>	States;
	MonsterStateBase*														CurState		= nullptr;
	MonsterBase*																MonsterPtr	= nullptr;

	inline void SetMonser(MonsterBase* _Mon)
	{
		MonsterPtr = _Mon;
	}

	void Start();
	void Update(float _DeltaTime);
	void Render(float _DeltaTime);

	MonsterFSM();
	~MonsterFSM();
};

