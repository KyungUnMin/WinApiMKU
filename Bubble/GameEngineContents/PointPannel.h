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

	static void AddPoint(int _Score);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static unsigned int	NowPoint;
	static unsigned int	HighPoint;
	static std::string		NowScoreStr;
	static std::string		HighScoreStr;

	TextLine*		Texts[2][3]			= { {nullptr,nullptr,nullptr},{nullptr,nullptr,nullptr} };

	void ResourceLoad();
	void CreatePannel();
	void CreateText();

	void Update_Score();
	void Update_2PText(float _DeltaTime);
};

