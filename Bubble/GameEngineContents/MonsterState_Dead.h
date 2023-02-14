#pragma once


class MonsterState_Dead
{
public:
	MonsterState_Dead();
	~MonsterState_Dead();

	MonsterState_Dead(const MonsterState_Dead& _Other) = delete;
	MonsterState_Dead(MonsterState_Dead&& _Other) noexcept = delete;
	MonsterState_Dead& operator=(const MonsterState_Dead& _Other) = delete;
	MonsterState_Dead& operator=(const MonsterState_Dead&& _Other) noexcept = delete;

protected:

private:

};

