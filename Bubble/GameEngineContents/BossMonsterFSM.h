#pragma once
#include <vector>

enum class BossStateType
{
	CircleMove,


	Count
};

class BossMonster;
class BossStateBase;

class BossMonsterFSM
{
public:
	BossMonsterFSM(BossMonster* _Boss);
	~BossMonsterFSM();

	BossMonsterFSM(const BossMonsterFSM& _Other) = delete;
	BossMonsterFSM(BossMonsterFSM&& _Other) noexcept = delete;
	BossMonsterFSM& operator=(const BossMonsterFSM& _Other) = delete;
	BossMonsterFSM& operator=(const BossMonsterFSM&& _Other) noexcept = delete;

	void Start();
	void Update(float _DeltaTime);
	void Render(float _DeltaTime);

	inline BossMonster* GetBoss()
	{
		return BossPtr;
	}

	void ChangeState(BossStateType _NextType);

protected:

private:
	BossMonster*								BossPtr		= nullptr;

	std::vector<BossStateBase*>		States;
	BossStateType							CurState		= BossStateType::Count;

	void CreateState(BossStateType _Type);
};

