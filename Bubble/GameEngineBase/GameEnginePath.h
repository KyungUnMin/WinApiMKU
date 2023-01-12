#pragma once
#include <filesystem>
#include <string>
#include <string_view>

class GameEnginePath
{
public:
	GameEnginePath();
	GameEnginePath(std::filesystem::path _Path);
	GameEnginePath(const std::string& _Path);
	~GameEnginePath();

	GameEnginePath(const GameEnginePath& _Other);
	GameEnginePath(GameEnginePath&& _Other) noexcept;

	GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	GameEnginePath& operator=(const GameEnginePath&& _Other) noexcept = delete;


	//������� Path�� string���� ��ȯ�ϴ� �Լ�
	std::string GetPathToString() const;

	//������� Path�� ���ܰ�θ� ��ȯ
	std::string GetFileName() const;


	//���� ��η� �̵�
	void MoveParent();

	//Ư�� ��ΰ� �����Ҷ� ���� ���������� �̵�
	void MoveParentToChildPath(const std::string_view& _String);

	//������� Path�� ��ȿ�� ������� Ȯ��
	bool IsExists();

	//���ڷ� �־��� String�� ������� Path�� ���������� ��ΰ� ��ȿ���� üũ
	bool IsExistsToPlusString(const std::string_view& _String);

	//������� Path�� �ֻ��� �������� Ȯ��
	bool IsRoot();

	//���� ��ġ���� ���ڷ� �־��� �ڽİ�η� �̵�
	bool Move(const std::string_view& _Path);

protected:

private:
	std::filesystem::path Path;
};

