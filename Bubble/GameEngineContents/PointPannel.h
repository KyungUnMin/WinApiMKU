#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;
class TextLine;

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
	GameEngineRender*	RenderPtr			= nullptr;
	TextLine*						PlayerPoint			= nullptr;
	TextLine*						HighScoreText		= nullptr;
	TextLine*						MoneyText			= nullptr;

	void ResourceLoad();
	void CreatePannel();
};

