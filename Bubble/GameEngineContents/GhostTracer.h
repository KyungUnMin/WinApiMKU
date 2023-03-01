#pragma once
#include "MovableActor.h"

/*
플레이어가 생성하는 방식으로 하자
*/

class GameEngineRender;
class GameEngineCollision;

class GhostTracer : public MovableActor
{
public:
	static const std::string_view RightImgPath;
	static const std::string_view LeftImgPath;
	static const std::string_view SmokeImgPath;

	static const std::string_view	IdleAniName;
	static const std::string_view	TraceAniName;


	GhostTracer();
	~GhostTracer();

	GhostTracer(const GhostTracer& _Other) = delete;
	GhostTracer(GhostTracer&& _Other) noexcept = delete;
	GhostTracer& operator=(const GhostTracer& _Other) = delete;
	GhostTracer& operator=(const GhostTracer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	enum class State
	{
		Idle,
		TraceY,
		TraceX
	};

	GameEngineRender*		GhostRender	= nullptr;
	GameEngineRender*		SmokeRender	= nullptr;
	GameEngineCollision*		CollisionPtr		= nullptr;

	float Timer = 0.f;

	void ResourceLoad();
	void CreateComponent();
	void CreateAnimations();
};

