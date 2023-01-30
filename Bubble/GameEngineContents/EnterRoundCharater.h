#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;

class EnterRoundCharater : public GameEngineActor
{
public:
	//���ڷ� ���� ĳ���� Ÿ�Կ� ���� �ִϸ��̼� ���� �� ���
	void SetCharacter(int _CharacterIndex);

	EnterRoundCharater();
	~EnterRoundCharater();

	EnterRoundCharater(const EnterRoundCharater& _Other) = delete;
	EnterRoundCharater(EnterRoundCharater&& _Other) noexcept = delete;
	EnterRoundCharater& operator=(const EnterRoundCharater& _Other) = delete;
	EnterRoundCharater& operator=(const EnterRoundCharater&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	//���� ����
	float				Radian			= 0.f;

	//1�ʴ� ���� ������(����)
	const float		AddRadian	= 1.f;

	//������
	float				Radius			= 100.f;

	GameEngineRender* PlayerRender = nullptr;
	GameEngineRender* BubbleRender = nullptr;
};

