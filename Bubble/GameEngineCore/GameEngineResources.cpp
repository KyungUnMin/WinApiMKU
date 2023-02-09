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
		MsgAssert("�̹� �ε��� �̹����� �� �ε��Ϸ��� �߽��ϴ�." + UpperName);
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
		MsgAssert("�ε����� ���� �̹����� ����Ϸ��� �߽��ϴ�" + UpperName);
		return nullptr;
	}

	return FindIter->second;
}



//////////////////////////SOUND////////////////


GameEngineSound* GameEngineResources::SoundLoad(const GameEnginePath& _Path)
{
	return SoundLoad(_Path.GetPathToString().c_str(), _Path.GetFileName().c_str());
}

//���带 ����ϱ� ���� �ε��ϱ�
GameEngineSound* GameEngineResources::SoundLoad(const std::string_view& _Path, const std::string_view& _Name)
{
	//�̹� �ε��� �������� üũ
	std::string UpperName = GameEngineString::ToUpper(_Name);
	if (AllSound.end() != AllSound.find(UpperName))
	{
		MsgAssert("�̹� �ε��� ���带 �� �ε��Ϸ��� �߽��ϴ�." + UpperName);
		return nullptr;
	}

	//�������� ���� �ε�
	GameEngineSound* NewSound = new GameEngineSound;
	NewSound->SoundLoad(_Path);

	//�ڷᱸ���� �����ϱ�
	AllSound.insert(std::make_pair(UpperName, NewSound));
	return NewSound;
}

//AllSound���� �̸����� Ư�� ���� ã��
GameEngineSound* GameEngineResources::SoundFind(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	std::map<std::string, GameEngineSound*>::iterator FindIter = AllSound.find(UpperName);
	if (AllSound.end() == FindIter)
	{
		MsgAssert("�ε����� ���� ���带 ����Ϸ��� �߽��ϴ�");
		return nullptr;
	}
	
	return FindIter->second;
}

//1���� ���带 ����
void GameEngineResources::SoundPlay(const std::string_view& _Name)
{
	GameEngineSound* Sound = SoundFind(_Name);
	FMOD::Channel* Ch = Sound->Play();
	Ch->setLoopCount(0);
}

//���带 �����Ű�� ���带 ��Ʈ�� �Ҽ� �ִ� ����ä���� ��� GameEngineSoundPlayer�� ��ȯ
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
		MsgAssert("��������� ���� ���带 ��Ʈ���ϰڴٰ� �߽��ϴ�");
		return;
	}

	ControlChannel->setLoopCount(_Count - 1);
}

void GameEngineSoundPlayer::Volume(float _Volume)
{
	if (nullptr == ControlChannel)
	{
		MsgAssert("��������� ���� ���带 ��Ʈ���ϰڴٰ� �߽��ϴ�");
		return;
	}

	ControlChannel->setVolume(_Volume);
}


void GameEngineSoundPlayer::Stop()
{
	if (nullptr == ControlChannel)
	{
		MsgAssert("��������� ���� ���带 ��Ʈ���ϰڴٰ� �߽��ϴ�");
		return;
	}

	ControlChannel->stop();
}



