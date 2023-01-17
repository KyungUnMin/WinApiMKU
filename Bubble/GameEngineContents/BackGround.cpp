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
		MsgAssert(UpperName + " 레벨에서 BackGround를 생성한 적이 없습니다.");
	}

	return FindIter->second;
}

BackGround* BackGround::Find(const std::string_view& _LevelName, size_t _Index)
{
	const std::vector<BackGround*>& VecBackGround = GetBackGrounds(_LevelName);

	if (VecBackGround.size() <= _Index)
	{
		MsgAssert("해당 백그라운드 벡터의 인덱스 범위를 넘어서 접근하였습니다");
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
		MsgAssert("해당 렌더 벡터의 인덱스 범위를 넘어서 접근하였습니다");
		return nullptr;
	}

	return Renders[_Index];
}
