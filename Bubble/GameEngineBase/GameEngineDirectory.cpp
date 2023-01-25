#include "GameEngineDirectory.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineDirectory::GameEngineDirectory()
{
}

GameEngineDirectory::~GameEngineDirectory()
{
}


//���ڷ� ���� _String�� �ִ� �� ���� �θ� ��η� �̵�
void GameEngineDirectory::MoveParentToDirectory(const std::string_view& _String)
{
	std::string MovePath = "\\";
	MovePath += _String;

	Path.MoveParentToChildPath(MovePath.c_str());
}


//���丮 �󿡼� ���ڷ� ���� �ڽ� ��η� �̵�
bool GameEngineDirectory::Move(const std::string_view& _String)
{
	std::string MovePath = "\\";
	MovePath += _String;
	return Path.Move(MovePath.c_str());
}


//������� Path�� ���ڷ� ���� _String�� ��ģ ��θ� ���� ����� ��ȯ
GameEnginePath GameEngineDirectory::GetPlusFileName(const std::string_view& _String)
{

	std::string PathString = Path.GetPathToString();
	PathString += "\\";
	PathString += _String;

	return GameEnginePath(PathString);
}


//���丮 �󿡼� �θ� ��η� �̵�
bool GameEngineDirectory::MoveParent()
{
	if (true == Path.IsRoot())
	{
		MsgAssert("��Ʈ ���丮�� �θ���丮�� �̵��Ҽ� �����ϴ�.");
		return false;
	}

	Path.MoveParent();

	return true;
}