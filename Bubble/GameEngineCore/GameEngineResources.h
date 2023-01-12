#pragma once

#include <map>
#include <string>
#include <GameEnginePlatform/GameEngineImage.h>

class GameEnginePath;
class GameEngineImage;

class GameEngineResources
{
public:
	GameEngineResources(const GameEngineResources& _Other) = delete;
	GameEngineResources(GameEngineResources&& _Other) noexcept = delete;
	GameEngineResources& operator=(const GameEngineResources& _Other) = delete;
	GameEngineResources& operator=(GameEngineResources&& _Other) noexcept = delete;

	static GameEngineResources& GetInst()
	{
		return Inst;
	}

	GameEngineImage* ImageLoad(const GameEnginePath& _Path);

	GameEngineImage* ImageLoad(const std::string_view& _Path, const std::string_view& _Name);

	GameEngineImage* ImageFind(const std::string_view& _Name);

	void Release();

protected:

private:
	static GameEngineResources	Inst;
	std::map<std::string, GameEngineImage*> AllImage;

	GameEngineResources();
	~GameEngineResources();
};

