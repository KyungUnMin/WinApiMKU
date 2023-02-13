#pragma once
#include "MovableActor.h"

class GameEngineCollision;
class GameEngineRender;
class MonsterFSM;
enum class MonsterStateType;

class MonsterBase : public MovableActor
{
public:
	static const float4 RenderScale;
	static const float4 CollisionScale;
	static const float4 CollisionOffset;

	MonsterBase();
	~MonsterBase() override;

	MonsterBase(const MonsterBase& _Other) = delete;
	MonsterBase(MonsterBase&& _Other) noexcept = delete;
	MonsterBase& operator=(const MonsterBase& _Other) = delete;
	MonsterBase& operator=(const MonsterBase&& _Other) noexcept = delete;

	inline GameEngineRender* GetRender()
	{
		return RenderPtr;
	}

	inline GameEngineCollision* GetCollision()
	{
		return CollisionPtr;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) final;
	void Render(float _DeltaTime) override;

	inline MonsterFSM* GetFSM()
	{
		return FsmPtr;
	}

	void Start_FSM(MonsterStateType _StartType);

private:
	GameEngineRender*		RenderPtr	= nullptr;
	GameEngineCollision*		CollisionPtr	= nullptr;
	MonsterFSM*					FsmPtr			= nullptr;
};

