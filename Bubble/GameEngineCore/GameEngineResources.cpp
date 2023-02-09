#include "GameEngineResources.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEnginePath.h>
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
	for (std::pair<std::string, GameEngineImage*> Pair : AllImage)
	{
		if (nullptr == Pair.second)
		{
			continue;
		}
		delete Pair.second;
	}
	AllImage.clear();


	for (std::pair<std::string, GameEngineSound*> Pair : AllSound)
	{
		if (nullptr == Pair.second)
		{
			continue;
		}
		delete Pair.second;
	}
	AllSound.clear();
}



GameEngineImage* GameEngineResources::ImageLoad(const GameEnginePath& _Path)
{
	return ImageLoad(_Path.GetPathToString().c_str(), _Path.GetFileName().c_str());
}


GameEngineImage* GameEngineResources::ImageLoad(const std::string_view& _Path, const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (AllImage.end() != AllImage.find(UpperName))
	{
		MsgAssert("이미 로드한 이미지를 또 로드하려고 했습니다." + UpperName);
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->ImageLoad(_Path);
	AllImage.insert(std::make_pair(UpperName, NewImage));
	return NewImage;
}



GameEngineImage* GameEngineResources::ImageFind(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	std::map<std::string, GameEngineImage*>::iterator FindIter = AllImage.find(UpperName);

	if (AllImage.end() == FindIter)
	{
		MsgAssert("로드하지 않은 이미지를 사용하려고 했습니다" + UpperName);
		return nullptr;
	}

	return FindIter->second;
}



//////////////////////////SOUND////////////////


GameEngineSound* GameEngineResources::SoundLoad(const GameEnginePath& _Path)
{
	return SoundLoad(_Path.GetPathToString().c_str(), _Path.GetFileName().c_str());
}

//사운드를 사용하기 위해 로드하기
GameEngineSound* GameEngineResources::SoundLoad(const std::string_view& _Path, const std::string_view& _Name)
{
	//이미 로드한 사운드인지 체크
	std::string UpperName = GameEngineString::ToUpper(_Name);
	if (AllSound.end() != AllSound.find(UpperName))
	{
		MsgAssert("이미 로드한 사운드를 또 로드하려고 했습니다." + UpperName);
		return nullptr;
	}

	//실질적인 사운드 로드
	GameEngineSound* NewSound = new GameEngineSound;
	NewSound->SoundLoad(_Path);

	//자료구조에 저장하기
	AllSound.insert(std::make_pair(UpperName, NewSound));
	return NewSound;
}

//AllSound에서 이름으로 특정 사운드 찾기
GameEngineSound* GameEngineResources::SoundFind(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	std::map<std::string, GameEngineSound*>::iterator FindIter = AllSound.find(UpperName);
	if (AllSound.end() == FindIter)
	{
		MsgAssert("로드하지 않은 사운드를 사용하려고 했습니다");
		return nullptr;
	}
	
	return FindIter->second;
}

//1번만 사운드를 실행
void GameEngineResources::SoundPlay(const std::string_view& _Name)
{
	GameEngineSound* Sound = SoundFind(_Name);
	FMOD::Channel* Ch = Sound->Play();
	Ch->setLoopCount(0);
}

//사운드를 실행시키고 사운드를 컨트롤 할수 있는 사운드채널이 담긴 GameEngineSoundPlayer를 반환
GameEngineSoundPlayer GameEngineResources::SoundPlayerToControl(const std::string_view& _Name)
{
	GameEngineSound* Sound = SoundFind(_Name);
	return GameEngineSoundPlayer(Sound->Play());
}








GameEngineSoundPlayer::GameEngineSoundPlayer(FMOD::Channel* _Channel)
	:ControlChannel(_Channel)
{

}


void GameEngineSoundPlayer::LoopCount(int _Count)
{
	if (nullptr == ControlChannel)
	{
		MsgAssert("재생하지도 않은 사운드를 컨트롤하겠다고 했습니다");
		return;
	}

	ControlChannel->setLoopCount(_Count - 1);
}

void GameEngineSoundPlayer::Volume(float _Volume)
{
	if (nullptr == ControlChannel)
	{
		MsgAssert("재생하지도 않은 사운드를 컨트롤하겠다고 했습니다");
		return;
	}

	ControlChannel->setVolume(_Volume);
}


void GameEngineSoundPlayer::Stop()
{
	if (nullptr == ControlChannel)
	{
		MsgAssert("재생하지도 않은 사운드를 컨트롤하겠다고 했습니다");
		return;
	}

	ControlChannel->stop();
}



