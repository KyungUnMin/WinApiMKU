#pragma once
#include "MovableActor.h"

class GameEngineRender;
class GameEngineCollision;
class MonsterBase;

class NatureMissleBase : public MovableActor
{
public:
	static const float4	CollisionScale;
	static const float4	RenderScale;
	static void AllMissleClear();

	NatureMissleBase();
	~NatureMissleBase() override;

	NatureMissleBase(const NatureMissleBase& _Other) = delete;
	NatureMissleBase(NatureMissleBase&& _Other) noexcept = delete;
	NatureMissleBase& operator=(const NatureMissleBase& _Other) = delete;
	NatureMissleBase& operator=(const NatureMissleBase&& _Other) noexcept = delete;

protected:
	void Start() override;

	inline GameEngineRender* GetRender()
	{
		return RenderPtr;
	}

	inline GameEngineCollision* GetCollision()
	{
		return CollisionPtr;
	}

	bool CollisionCheckWithPlayer();
	bool CollisionCheckWithMonster(std::vector<MonsterBase*>& _Monsters);

private:
	GameEngineRender*		RenderPtr		= nullptr;
	GameEngineCollision*		CollisionPtr		= nullptr;
};

