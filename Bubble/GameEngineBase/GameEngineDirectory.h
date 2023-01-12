#pragma once
#include <string_view>
#include <vector>
#include "GameEnginePath.h"

class GameEngineFile;

//Path�� �����ϴ� Ŭ����
class GameEngineDirectory
{
public:
	GameEngineDirectory();
	~GameEngineDirectory();

	GameEngineDirectory(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory(GameEngineDirectory&& _Other) noexcept = delete;
	GameEngineDirectory& operator=(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory& operator=(const GameEngineDirectory&& _Other) noexcept = delete;

	//bool IsFile(const std::string_view& _FileName);

	//���丮 �󿡼� �θ� ��η� �̵�
	bool MoveParent();

	//���ڷ� ���� _String�� �ִ� �� ���� �θ� ��η� �̵�
	void MoveParentToDirectory(const std::string_view& _String);

	//���丮 �󿡼� ���ڷ� ���� �ڽ� ��η� �̵�
	bool Move(const std::string_view& _String);

	//������� Path�� ���ڷ� ���� _String�� ��ģ ��θ� ���� ����� ��ȯ
	GameEnginePath GetPlusFileName(const std::string_view& _String);

protected:


private:
	GameEnginePath Path;
};

