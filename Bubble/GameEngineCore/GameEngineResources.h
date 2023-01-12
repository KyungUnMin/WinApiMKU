#pragma once
#include <string>
#include <map>
#include <GameEnginePlatform/GameEngineImage.h>

class GameEnginePath;

class GameEngineResources
{
public:
	GameEngineResources(const GameEngineResources& _Other) = delete;
	GameEngineResources(GameEngineResources&& _Other) noexcept = delete;
	GameEngineResources& operator=(const GameEngineResources& _Other) = delete;
	GameEngineResources& operator=(const GameEngineResources&& _Other) noexcept = delete;

	static GameEngineResources& GetInst()
	{
		return Inst;
	}

	GameEngineImage* ImageLoad(const GameEnginePath& _Path);

	GameEngineImage* ImageLoad(const std::string_view& _Path, const std::string& _Name);

	GameEngineImage* ImageFind(const std::string_view& _Name);

	void Release();

protected:


private:
	static GameEngineResources Inst;
	std::map<std::string, GameEngineImage*> AllImage;

	GameEngineResources();
	~GameEngineResources();
};

