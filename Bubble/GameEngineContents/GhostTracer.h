#pragma once
#include "MovableActor.h"

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

	static GhostTracer* MainGhost;

	GhostTracer();
	~GhostTracer() override;

	GhostTracer(const GhostTracer& _Other) = delete;
	GhostTracer(GhostTracer&& _Other) noexcept = delete;
	GhostTracer& operator=(const GhostTracer& _Other) = delete;
	GhostTracer& operator=(const GhostTracer&& _Other) noexcept = delete;

	void SetDir(const float4& _Dir) override;

	void KillPlayer();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	enum class State
	{
		Idle,
		TraceY,
		TraceX,
		PlayerKill
	};

	State								CurState			= State::Idle;
	State								PrevState			= State::TraceX;
	GameEngineRender*		GhostRender	= nullptr;
	GameEngineRender*		SmokeRender	= nullptr;
	GameEngineCollision*		CollisionPtr		= nullptr;

	float								Timer				= 0.f;
	const float						StartDuration	= 5.f;
	float								NowDuration	= StartDuration;
	const float						NextDurPer		= 0.8f;
	float4								StartPos			= float4::Zero;
	float4								DestPos			= float4::Zero;

	HPEN								DebugPen		= HPEN();

	void ResourceLoad();
	void CreateComponent();
	void CreateAnimations();

	void Update_Idle(float _DeltaTime);
	void Update_TraceY(float _DeltaTime);
	void Update_TraceX(float _DeltaTime);

	const float4 CalcLerpDir();
	void PlayerCollisionCheck();

	void DrawDebugArrow(const float4& _Start, const float4& _End);
};

