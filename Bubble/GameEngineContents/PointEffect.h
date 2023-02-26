#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;

class PointEffect : public GameEngineActor
{
public:
	static const std::string_view ImagePath;
	static const std::vector<int> ImageScores;

	PointEffect();
	~PointEffect() override;

	PointEffect(const PointEffect& _Other) = delete;
	PointEffect(PointEffect&& _Other) noexcept = delete;
	PointEffect& operator=(const PointEffect& _Other) = delete;
	PointEffect& operator=(const PointEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void Update_Scale();

	inline void SetMoveSpeed(const float4& _MoveSpeed)
	{
		MoveSpeed = _MoveSpeed;
	}

	inline void SetMaxScale(const float4& _Scale)
	{
		MaxSize = _Scale;
	}

	inline void SetRender(GameEngineRender* _Render)
	{
		RenderPtr = _Render;
	}

private:
	GameEngineRender*	RenderPtr		= nullptr;
	const float					AliveTime			= 2.f;
	float4							MoveSpeed		= float4{ 0.f, 100.f };
	float4							MaxSize			= float4{ 75.f, 75.f };

	void ResourceLoad();
	void SelectImageFrame();
};

