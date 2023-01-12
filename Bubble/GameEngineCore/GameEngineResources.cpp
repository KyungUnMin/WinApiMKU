#include "GameEngineResources.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>

GameEngineResources GameEngineResources::Inst;

GameEngineResources::GameEngineResources()
{

}

GameEngineResources::~GameEngineResources()
{

}

void GameEngineResources::Release()
{
	for (auto Pair : AllImage)
	{
		if (nullptr != Pair.second)
		{
			delete Pair.second;
		}
	}

	AllImage.clear();
}


GameEngineImage* GameEngineResources::ImageLoad(const GameEnginePath& _Path)
{
	return ImageLoad(_Path.GetPathToString().c_str(), _Path.GetFileName().c_str());
}

GameEngineImage* GameEngineResources::ImageLoad(const std::string_view& _Path, const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);
	if (AllImage.end() != AllImage.find(UpperName))
	{
		MsgAssert(UpperName + " : 이미 로드한 이미지를 또 로드하려고 함");
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage;
	NewImage->ImageLoad(_Path);
	AllImage.insert(std::make_pair(UpperName, NewImage));
	return NewImage;
}

GameEngineImage* GameEngineResources::ImageFind(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);
	auto FindIter = AllImage.find(UpperName);
	if (AllImage.end() == FindIter)
	{
		MsgAssert(UpperName + " : 로드하지 않은 이미지를 사용");
		return nullptr;
	}

	return FindIter->second;
}

