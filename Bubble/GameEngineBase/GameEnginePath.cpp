#include "GameEnginePath.h"
#include <Windows.h>
#include <io.h>
#include <GameEngineBase/GameEngineDebug.h>

GameEnginePath::GameEnginePath()
	: Path(std::filesystem::current_path())
{
}

GameEnginePath::GameEnginePath(std::filesystem::path _Path)
	: Path(_Path)
{
}



GameEnginePath::GameEnginePath(const std::string& _Path)
	: Path(_Path)
{

}

GameEnginePath::GameEnginePath(GameEnginePath&& _Other)
	: Path(_Other.Path)
{

}



GameEnginePath::~GameEnginePath()
{
}










GameEnginePath::GameEnginePath(const GameEnginePath& _Other)
	: Path(_Other.Path)
{

}


//������� Path�� ���ܰ�θ� ��ȯ
std::string GameEnginePath::GetFileName() const
{
	return Path.filename().string();
}


//������� Path�� string���� ��ȯ�ϴ� �Լ�
std::string GameEnginePath::GetPathToString() const
{
	return Path.string();
}


//���� ��η� �̵�
void GameEnginePath::MoveParent()
{
	Path = Path.parent_path();
}


//Ư�� ��ΰ� �����Ҷ� ���� ���������� �̵�
void GameEnginePath::MoveParentToChildPath(const std::string_view& _String)
{
	while (false == IsRoot())
	{
		//ã�� ��ΰ� ���� ��ġ���� �ڽ����� �����Ѵٸ� return
		if (true == IsExistsToPlusString(_String))
		{
			return;
		}

		//���ٸ� ������� Path�� �θ���ġ�� �̵�
		MoveParent();
	}

	//�ֻ��� ��α��� ���µ��� ã�� ���ߴٸ� Assert
	MsgAssert("�̷� ��θ� �ڽ����� ���� �θ�� �������� �ʽ��ϴ�.");
}


//���� ��ġ���� ���ڷ� �־��� �ڽİ�η� �̵�
bool GameEnginePath::Move(const std::string_view& _Path)
{
	Path += _Path;

	if (false == IsExists())
	{
		MsgAssert("�������� �ʴ� ��η� �̵��Ϸ��� �߽��ϴ�.");
		return false;
	}

	return true;
}


//������� Path�� �ֻ��� �������� Ȯ��
bool GameEnginePath::IsRoot()
{
	return Path.root_path() == Path;
}


//������� Path�� ��ȿ�� ������� Ȯ��
bool GameEnginePath::IsExists()
{
	//���� ��ġ�� ��ΰ� ��ȿ�Ѱ�
	return 0 == _access(Path.string().c_str(), 0);
}


//���ڷ� �־��� String�� ������� Path�� ���������� ��ΰ� ��ȿ���� üũ
bool GameEnginePath::IsExistsToPlusString(const std::string_view& _String)
{
	//(������� Path)���� ��� + ���ڷ� ���� ���
	std::string Str = GetPathToString() + _String.data();
	return 0 == _access(Str.c_str(), 0);
}


//���ڷ� ���� string���� �ּҸ� ����
void GameEnginePath::SetPath(const std::string_view& _Path)
{
	Path = _Path.data();
}