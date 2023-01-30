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

	//생성된 거품들을 모두 지우고 vector를 clear
	void Reset();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	//생성된 거품들을 보관하는 벡터<라디언 각도, 포인터>
	std::vector<std::pair<float, GameEngineRender*>> Bubbles;

	//거품 생성기의 6방향
	float				Dir[6]						= { 0.f, };
	//거품 생성기 회전 속도
	const float		RotateSpeed			= 0.1f;

	//하나의 거품이 이동하는 속도
	const float		MoveSpeed				= 100.f;
	//거품 생성 주기
	const float		BubbleSpawnTime	= 0.15f;
	//거품 크기 증가속도
	const float		BubbleGrowSpeed	= 50.f;
	//거품의 최대크기
	const float4	BubbleMaxScale		= { 200.f, 200.f };


	float				AccTime					= 0.0f;
	int					SpawnIndex			= 0;

	//지금까지 생성되었던 거품을 이동
	void BubbleMove(float _DeltaTime);
	//지금까지 생성되었던 거품의 크기를 증가
	void BubbleScaleUp(float _DeltaTime);
	// 거품을 생성
	void BubbleCreate(float _DirRadian);
};

