#include "GameEngineSound.h"
#include <GameEngineBase/GameEngineDebug.h>

#ifdef _DEBUG
#pragma comment(lib, "GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmodL_vc.lib")
#else
#pragma comment(lib, "GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmod_vc.lib")
#endif

//�ý��� ����
FMOD::System* SoundSystem = nullptr;

//�����ڸ� �̿��� �ý��� ���� �Ҵ�
class SoundSystemCreator
{
public:
	SoundSystemCreator()
	{
		//�ý��� ���� ����
		FMOD::System_Create(&SoundSystem);
		if (nullptr == SoundSystem)
		{
			MsgAssert("���� �ʱ�ȭ�� ����� ���� �ʾҽ��ϴ�");
		}

		//�ý��� ���� �ʱ�ȭ
		if (FMOD_OK != SoundSystem->init(32, FMOD_DEFAULT, nullptr))
		{
			MsgAssert("���� �ý��� �̴ϼȶ���� �����߽��ϴ�");
		}
	}

	//�ý��� ���� ����
	~SoundSystemCreator()
	{
		SoundSystem->release();
	}
};

SoundSystemCreator SoundInitObject;

void GameEngineSound::SoundUpdate()
{
	if (nullptr == SoundSystem)
	{
		MsgAssert("���� ������Ʈ�� �Ұ����մϴ�");
		return;
	}

	SoundSystem->update();
}








GameEngineSound::GameEngineSound()
{

}

GameEngineSound::~GameEngineSound()
{

}

void GameEngineSound::SoundLoad(const std::string_view& _Path)
{
	if (FMOD_OK != SoundSystem->createSound(_Path.data(), FMOD_LOOP_NORMAL, nullptr, &FMODSound))
	{
		MsgAssert(std::string("���� �ε忡 �����Ͽ����ϴ�.\n��� : ") + _Path.data());
	}
}

FMOD::Channel* GameEngineSound::Play()
{
	if (nullptr == FMODSound)
	{
		MsgAssert("FMODSound�� nullptr�Դϴ�");
	}

	FMOD::Channel* Return;
	SoundSystem->playSound(FMODSound, nullptr, false, &Return);
	return Return;
}
