#pragma once
#include "MovableActor.h"

class GameEngineCollision;

class MonsterBase : public MovableActor
{
public:
	MonsterBase();
	~MonsterBase() override;

	MonsterBase(const MonsterBase& _Other) = delete;
	MonsterBase(MonsterBase&& _Other) noexcept = delete;
	MonsterBase& operator=(const MonsterBase& _Other) = delete;
	MonsterBase& operator=(const MonsterBase&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineCollision* CollisionPtr = nullptr;

	void ResourceLoad();
};

