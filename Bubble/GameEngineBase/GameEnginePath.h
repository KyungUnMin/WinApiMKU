#pragma once
#include <filesystem>

class GameEnginePath
{
public:
	friend class GameEngineFile;
	friend class GameEngineDirectory;

	GameEnginePath();
	GameEnginePath(std::filesystem::path _Path);
	GameEnginePath(const std::string& _Path);
	~GameEnginePath();

	GameEnginePath(const GameEnginePath& _Other);
	GameEnginePath(GameEnginePath&& _Other);
	GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;

	//������� Path�� ���ܰ�θ� ��ȯ
	std::string GetFileName() const;

	//������� Path�� string���� ��ȯ�ϴ� �Լ�
	std::string GetPathToString() const;

	//���� ��η� �̵�
	void MoveParent();

	//Ư�� ��ΰ� �����Ҷ� ���� ���������� �̵�
	void MoveParentToChildPath(const std::string_view& _String);

	//������� Path�� ��ȿ�� ������� Ȯ��
	bool IsExists();

	//���ڷ� �־��� String�� ������� Path�� ���������� ��ΰ� ��ȿ���� üũ
	bool IsExistsToPlusString(const std::string_view& _String);

	// bool MoveParentToChildPath(const std::string_view& _IOName );

	//������� Path�� �ֻ��� �������� Ȯ��
	bool IsRoot();

	//���� ��ġ���� ���ڷ� �־��� �ڽİ�η� �̵�
	bool Move(const std::string_view& _Path);

	//���ڷ� ���� string���� �ּҸ� ����
	void SetPath(const std::string_view& _Path);


protected:

private:
	std::filesystem::path Path;

};

