#include "GameEngineDirectory.h"
#include "GameEngineDebug.h"

GameEngineDirectory::GameEngineDirectory()
{

}

GameEngineDirectory::~GameEngineDirectory()
{

}

//디렉토리 상에서 부모 경로로 이동
bool GameEngineDirectory::MoveParent()
{
	if (true == Path.IsRoot())
	{
		MsgAssert("루트 디렉토리는 부모 디렉토리로 이동할 수 없음");
		return false;
	}

	Path.MoveParent();
	return false;
}

//인자로 받은 _String이 있는 곳 까지 부모 경로로 이동
void GameEngineDirectory::MoveParentToDirectory(const std::string_view& _String)
{
	std::string MovePath = "\\";
	MovePath += _String;

	//MovePath가 있는 곳 까지 부모 경로로 이동
	Path.MoveParentToChildPath(MovePath.c_str());
}

//디렉토리 상에서 인자로 받은 자식 경로로 이동
bool GameEngineDirectory::Move(const std::string_view& _String)
{
	std::string MovePath = "\\";
	MovePath += _String;

	//현재 위치에서 MovePath (자식)경로로 이동
	return Path.Move(MovePath.c_str());
}


//멤버변수 Path와 인자로 받은 _String를 합친 경로를 새로 만들어 반환
GameEnginePath GameEngineDirectory::GetPlusFileName(const std::string_view& _String)
{
	std::string PathString = Path.GetPathToString();
	PathString += "\\";
	PathString += _String;

	return GameEnginePath(PathString);
}
