#pragma once
#include <vector>
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;

class RoundA_Enter_BackGround : public GameEngineActor
{
public:
	RoundA_Enter_BackGround();
	~RoundA_Enter_BackGround();

	RoundA_Enter_BackGround(const RoundA_Enter_BackGround& _Other) = delete;
	RoundA_Enter_BackGround(RoundA_Enter_BackGround&& _Other) noexcept = delete;
	RoundA_Enter_BackGround& operator=(const RoundA_Enter_BackGround& _Other) = delete;
	RoundA_Enter_BackGround& operator=(const RoundA_Enter_BackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;


private:
	std::vector<GameEngineRender*>	BackGrounds;
	const int											ImageIndex[4]	= { 5, 6, 4, 0 };

	const float										SkyMoveSpeed	= 10.f;
	float4												MoveDir				= { -1.f, 0.f };
	float												DirTime				= 0.0f;
	const float										DirChangeTime	= 20.f;
};

