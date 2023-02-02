#pragma once
#include "MovableActor.h"

class GameEngineCollision;
class GameEngineActor;
class GameEngineRender;

class MonsterBase : public MovableActor
{
public:
	MonsterBase();
	~MonsterBase() override;

	MonsterBase(const MonsterBase& _Other) = delete;
	MonsterBase(MonsterBase&& _Other) noexcept = delete;
	MonsterBase& operator=(const MonsterBase& _Other) = delete;
	MonsterBase& operator=(const MonsterBase&& _Other) noexcept = delete;

	void Reset();
	void BubbleLock(GameEngineActor* _Bubble);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRender*		Render			= nullptr;
	GameEngineCollision*		CollisionPtr	= nullptr;
	GameEngineActor*			LockBubble	= nullptr;

	void ResourceLoad();
};

