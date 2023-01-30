#pragma once
#include <vector>
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;

class EnterRoundBubble : public GameEngineActor
{
public:
	EnterRoundBubble();
	~EnterRoundBubble();

	EnterRoundBubble(const EnterRoundBubble& _Other) = delete;
	EnterRoundBubble(EnterRoundBubble&& _Other) noexcept = delete;
	EnterRoundBubble& operator=(const EnterRoundBubble& _Other) = delete;
	EnterRoundBubble& operator=(const EnterRoundBubble&& _Other) noexcept = delete;

	//������ ��ǰ���� ��� ����� vector�� clear
	void Reset();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	//������ ��ǰ���� �����ϴ� ����<���� ����, ������>
	std::vector<std::pair<float, GameEngineRender*>> Bubbles;

	//��ǰ �������� 6����
	float				Dir[6]						= { 0.f, };
	//��ǰ ������ ȸ�� �ӵ�
	const float		RotateSpeed			= 0.1f;

	//�ϳ��� ��ǰ�� �̵��ϴ� �ӵ�
	const float		MoveSpeed				= 100.f;
	//��ǰ ���� �ֱ�
	const float		BubbleSpawnTime	= 0.15f;
	//��ǰ ũ�� �����ӵ�
	const float		BubbleGrowSpeed	= 50.f;
	//��ǰ�� �ִ�ũ��
	const float4	BubbleMaxScale		= { 200.f, 200.f };


	float				AccTime					= 0.0f;
	int					SpawnIndex			= 0;

	//���ݱ��� �����Ǿ��� ��ǰ�� �̵�
	void BubbleMove(float _DeltaTime);
	//���ݱ��� �����Ǿ��� ��ǰ�� ũ�⸦ ����
	void BubbleScaleUp(float _DeltaTime);
	// ��ǰ�� ����
	void BubbleCreate(float _DirRadian);
};

