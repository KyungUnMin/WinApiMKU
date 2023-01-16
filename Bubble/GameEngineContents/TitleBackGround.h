#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;

class TitleBackGround : public GameEngineActor
{
public:
	TitleBackGround();
	~TitleBackGround();

	TitleBackGround(const TitleBackGround& _Other) = delete;
	TitleBackGround(TitleBackGround&& _Other) noexcept = delete;
	TitleBackGround& operator=(const TitleBackGround& _Other) = delete;
	TitleBackGround& operator=(const TitleBackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRender* BackCurtain = nullptr;
};

