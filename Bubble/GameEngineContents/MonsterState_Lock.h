#pragma once
#include "MonsterStateBase.h"

class MonsterState_Lock : public MonsterStateBase
{
public:
	MonsterState_Lock();
	~MonsterState_Lock() override;

	MonsterState_Lock(const MonsterState_Lock& _Other) = delete;
	MonsterState_Lock(MonsterState_Lock&& _Other) noexcept = delete;
	MonsterState_Lock& operator=(const MonsterState_Lock& _Other) = delete;
	MonsterState_Lock& operator=(const MonsterState_Lock&& _Other) noexcept = delete;

protected:
	void Start() override;
	void EnterState() override;

private:

};

