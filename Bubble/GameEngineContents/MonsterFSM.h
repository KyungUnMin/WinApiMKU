#pragma once
#include <map>
#include "MonsterStateEnum.h"

class MonsterStateBase;
class MonsterBase;

class MonsterFSM
{
public:
	friend class MonsterBase;

	MonsterFSM(const MonsterFSM& _Other) = delete;
	MonsterFSM(MonsterFSM&& _Other) noexcept = delete;
	MonsterFSM& operator=(const MonsterFSM& _Other) = delete;
	MonsterFSM& operator=(const MonsterFSM&& _Other) noexcept = delete;

	template <typename StateType>
	MonsterStateBase* CreateState(MonsterStateType _Type)
	{
		MonsterStateBase* StetePtr = new StateType;
		States[_Type] = StetePtr;
		return StetePtr;
	}

	void ChangeState(MonsterStateType _NextState);

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

