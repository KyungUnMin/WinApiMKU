#pragma once
#include <GameEngineCore/GameEngineLevel.h>

enum class SelectPlayerLevelRenderOrder
{
	BackGround,
	UI
};

class TextLine;

//현재까지는 이미지만 띄우고 아무키라도 누르면 다음 레벨로 넘어감
class SelectPlayerLevel : public GameEngineLevel
{
public:
	SelectPlayerLevel();
	~SelectPlayerLevel();

	SelectPlayerLevel(const SelectPlayerLevel& _Other) = delete;
	SelectPlayerLevel(SelectPlayerLevel&& _Other) noexcept = delete;
	SelectPlayerLevel& operator=(const SelectPlayerLevel& _Other) = delete;
	SelectPlayerLevel& operator=(const SelectPlayerLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override{}
	void LevelChangeStart(GameEngineLevel* _NextLevel) override{}

private:
	TextLine*			Text = nullptr;

	//OnOffTime 시간마다 Text가 꺼졌다가 켜진다.
	float				accTime = 0.0f;
	const float		OnOffTime = 0.5f;

	void ResourceLoad();
};

