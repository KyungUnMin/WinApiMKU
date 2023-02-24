#pragma once
#include "MovableActor.h"

class GameEngineRender;
class GameEngineCollision;
class BossMonsterFSM;

class BossMonster : public MovableActor
{
public:
	static const std::string_view RightImagePath;
	static const std::string_view LeftImagePath;
	static const std::string_view DeadImagePath;

	static const std::string_view IdleAniName;
	static const std::string_view AngryAniName;
	static const std::string_view RageAngryAniName;
	static const std::string_view LockAniName;
	static const std::string_view DeadAniName;

	static const float4 RenderScale;
	static const float4 CollisionScale;

	BossMonster();
	~BossMonster() override;

	BossMonster(const BossMonster& _Other) = delete;
	BossMonster(BossMonster&& _Other) noexcept = delete;
	BossMonster& operator=(const BossMonster& _Other) = delete;
	BossMonster& operator=(const BossMonster&& _Other) noexcept = delete;

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
	void Render(float _DeltaTime) final;

private:
	GameEngineRender*		RenderPtr		= nullptr;
	GameEngineCollision*		CollisionPtr		= nullptr;
	BossMonsterFSM*			FsmPtr				= nullptr;

	void ResourceLoad();
	void CreateComponent();
	void CreateAnimation();
};

