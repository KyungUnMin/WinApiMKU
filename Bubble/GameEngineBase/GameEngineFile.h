#pragma once
#include "GameEnginePath.h"

class GameEngineFile
{
public:
	GameEngineFile();
	~GameEngineFile();
	GameEngineFile(std::filesystem::path _Path);

	/*GameEngineFile(const GameEngineFile& _Other) = delete;
	GameEngineFile(GameEngineFile&& _Other) noexcept = delete;
	GameEngineFile& operator=(const GameEngineFile& _Other) = delete;
	GameEngineFile& operator=(const GameEngineFile&& _Other) noexcept = delete;*/

	std::string GetFullPath()
	{
		return Path.Path.string();
	}

protected:

private:
	GameEnginePath Path;
};

