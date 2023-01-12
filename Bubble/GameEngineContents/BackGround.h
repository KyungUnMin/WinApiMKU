#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string_view>
#include <string>

class GameEngineLevel;
class GameEngineImage;

class BackGround : public GameEngineActor
{
public:
	BackGround();
	~BackGround();

	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(const BackGround&& _Other) noexcept = delete;

	void Start() override;
	//void Update() override;
	void Render() override;

	void ImageFind(const std::string_view& _ImageKey);

	/*void SetUpdateCallBack(Update_CallBack _UpdateCallBack, GameEngineLevel* _Level)
	{
		UpdateCallBack = _UpdateCallBack;
		CurrentLevel = _Level;
	}*/

protected:

private:
	GameEngineImage*			Image					= nullptr;
	void(GameEngineLevel::* UpdateCallBack)(void)	= nullptr;
	//GameEngineLevel*			CurrentLevel		= nullptr;
};

