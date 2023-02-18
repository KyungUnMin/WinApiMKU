#pragma once
#include "MonsterStateBase.h"

class MonsterMissleBase;
class MonsterBase;

enum class MonMissleType
{
	MightARock,
	WarurinBress,

	UNKNOWN
};


class MonsterState_ThrowMissle : public MonsterStateBase
{
public:
	MonsterState_ThrowMissle();
	~MonsterState_ThrowMissle();

	MonsterState_ThrowMissle(const MonsterState_ThrowMissle& _Other) = delete;
	MonsterState_ThrowMissle(MonsterState_ThrowMissle&& _Other) noexcept = delete;
	MonsterState_ThrowMissle& operator=(const MonsterState_ThrowMissle& _Other) = delete;
	MonsterState_ThrowMissle& operator=(const MonsterState_ThrowMissle&& _Other) noexcept = delete;

	inline void SetMissleType(MonMissleType _MissleType)
	{
		MissleType = _MissleType;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;
	void ExitState() override;

private:
	static const float4		SpawnOffset;

	MonsterBase*				Monster		= nullptr;
	MonMissleType			MissleType	= MonMissleType::UNKNOWN;
	MonsterMissleBase*	Missle			= nullptr;

	MonsterMissleBase* CreateMissle(MonMissleType _Type);
};

