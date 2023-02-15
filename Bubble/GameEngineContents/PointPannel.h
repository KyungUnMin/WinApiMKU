#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BubbleDestHelper;
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
	const float					OffsetY				= 50.f;

	TextLine*						Texts[2][3]			= { {nullptr,nullptr,nullptr},{nullptr,nullptr,nullptr} };

	const float					ChangeTextTime	= 1.f;
	float							AccTime				= 0.0f;
	bool								IsFirstText			= true;

	unsigned int				NowPoint				= 0;
	unsigned int				HighPoint				= 0;

	void ResourceLoad();
	void CreatePannel();
	void CreateText();


};

