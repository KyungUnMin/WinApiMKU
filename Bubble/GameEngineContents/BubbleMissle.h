#pragma once
#include "MovableActor.h"
#include "ContentsEnum.h"

class GameEngineRender;
class GameEngineCollision;
class BubbleSpawner;
class BubbleMissleFSM;
class RoundLevelBase;
class MonsterBase;

class BubbleMissle : public MovableActor
{
	friend BubbleSpawner;

public:
	static const float4 RenderScale;
	static const float4 CollisionScale;

	BubbleMissle();
	virtual ~BubbleMissle() override;

	BubbleMissle(const BubbleMissle& _Other) = delete;
	BubbleMissle(BubbleMissle&& _Other) noexcept = delete;
	BubbleMissle& operator=(const BubbleMissle& _Other) = delete;
	BubbleMissle& operator=(const BubbleMissle&& _Other) noexcept = delete;

	inline GameEngineRender* GetRender()
	{
		return AniRender;
	}

	inline RoundLevelBase* GetRoundLevel()
	{
		return RoundLevel;
	}

	inline GameEngineCollision* GetCollisionPtr()
	{
		return CollisionPtr;
	}

	inline BubbleMissleFSM* GetFSM()
	{
		return FSM;
	}

	inline MonsterBase* GetLockMonster()
	{
		return LockMonster;
	}

	inline void SetLockMonster(MonsterBase* _LockMonster)
	{
		LockMonster = _LockMonster;
	}


protected:
	void Start() override;
	void Update(float _DeltaTime) final;
	
private:
	BubbleSpawner*				Spawner			= nullptr;
	GameEngineRender*		AniRender		= nullptr;
	GameEngineCollision*		CollisionPtr		= nullptr;

	BubbleMissleFSM*			FSM					= nullptr;
	RoundLevelBase*			RoundLevel		= nullptr;

	MonsterBase*					LockMonster	= nullptr;

	void Init(PlayerCharacterType _CharType, BubbleMissleType _BubbleType);
};

