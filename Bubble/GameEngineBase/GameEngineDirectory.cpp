#include "GameEngineDirectory.h"
#include "GameEngineDebug.h"

GameEngineDirectory::GameEngineDirectory()
{

}

GameEngineDirectory::~GameEngineDirectory()
{

}

//���丮 �󿡼� �θ� ��η� �̵�
bool GameEngineDirectory::MoveParent()
{
	if (true == Path.IsRoot())
	{
		MsgAssert("��Ʈ ���丮�� �θ� ���丮�� �̵��� �� ����");
		return false;
	}

	Path.MoveParent();
	return false;
}

//���ڷ� ���� _String�� �ִ� �� ���� �θ� ��η� �̵�
void GameEngineDirectory::MoveParentToDirectory(const std::string_view& _String)
{
	std::string MovePath = "\\";
	MovePath += _String;

	//MovePath�� �ִ� �� ���� �θ� ��η� �̵�
	Path.MoveParentToChildPath(MovePath.c_str());
}

//���丮 �󿡼� ���ڷ� ���� �ڽ� ��η� �̵�
bool GameEngineDirectory::Move(const std::string_view& _String)
{
	std::string MovePath = "\\";
	MovePath += _String;

	//���� ��ġ���� MovePath (�ڽ�)��η� �̵�
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
