#pragma once
#include "MovableActor.h"

class GameEngineRender;
class GameEngineCollision;



class MonsterMissleBase : public MovableActor
{
public:
	static const float4 RenderScale;
	static const float4 CollisionScale;

	MonsterMissleBase();
	~MonsterMissleBase();

	MonsterMissleBase(const MonsterMissleBase& _Other) = delete;
	MonsterMissleBase(MonsterMissleBase&& _Other) noexcept = delete;
	MonsterMissleBase& operator=(const MonsterMissleBase& _Other) = delete;
	MonsterMissleBase& operator=(const MonsterMissleBase&& _Other) noexcept = delete;

	inline GameEngineRender* GetRender()
	{
		return RenderPtr;
	}

	virtual void ThrowMissle(const float4& _Dir) = 0;

protected:
	void Start() override;

	bool PlayerCollisionCheck();

private:
	GameEngineRender*		RenderPtr		= nullptr;
	GameEngineCollision*		CollisionPtr		= nullptr;
};

