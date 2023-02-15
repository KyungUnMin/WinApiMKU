#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;
class BubbleDestHelper;

class PointPannel : public GameEngineActor
{
public:
	PointPannel();
	~PointPannel();

	PointPannel(const PointPannel& _Other) = delete;
	PointPannel(PointPannel&& _Other) noexcept = delete;
	PointPannel& operator=(const PointPannel& _Other) = delete;
	PointPannel& operator=(const PointPannel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	const float					OffsetY				= 50.f;
	GameEngineRender*	RenderPtr			= nullptr;

	void ResourceLoad();
	void CreatePannel();
	void CreateText();
};

