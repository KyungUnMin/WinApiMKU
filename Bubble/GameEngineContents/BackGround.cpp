#include "BackGround.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineLevel.h>

std::map<std::string, std::vector<BackGround*>> BackGround::BackGrounds;

const std::vector<BackGround*>& BackGround::GetBackGrounds(const std::string_view& _LevelName)
{
	std::string UpperName = GameEngineString::ToUpper(_LevelName);
	auto FindIter = BackGrounds.find(UpperName);

	if (BackGrounds.end() == FindIter)
	{
		MsgAssert(UpperName + " �������� BackGround�� ������ ���� �����ϴ�.");
	}

	return FindIter->second;
}

BackGround* BackGround::Find(const std::string_view& _LevelName, size_t _Index)
{
	const std::vector<BackGround*>& VecBackGround = GetBackGrounds(_LevelName);

	if (VecBackGround.size() <= _Index)
	{
		MsgAssert("�ش� ��׶��� ������ �ε��� ������ �Ѿ �����Ͽ����ϴ�");
		return nullptr;
	}

	return VecBackGround[_Index];
}

BackGround::BackGround()
{
	/*std::string LevelName = GetLevel()->GetName();
	BackGround::BackGrounds[LevelName].push_back(this);*/
}

BackGround::~BackGround()
{

}

GameEngineRender* BackGround::GetRender(size_t _Index)
{
	if (Renders.size() <= _Index)
	{
		MsgAssert("�ش� ���� ������ �ε��� ������ �Ѿ �����Ͽ����ϴ�");
		return nullptr;
	}

	return Renders[_Index];
}
