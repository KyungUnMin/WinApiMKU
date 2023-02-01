#pragma once
#include "RoundLevelBase.h"


class RoundA2Level : public RoundLevelBase
{
public:
	static const std::vector<float4> PlayerSpanwPos;

	RoundA2Level();
	~RoundA2Level();

	RoundA2Level(const RoundA2Level& _Other) = delete;
	RoundA2Level(RoundA2Level&& _Other) noexcept = delete;
	RoundA2Level& operator=(const RoundA2Level& _Other) = delete;
	RoundA2Level& operator=(const RoundA2Level&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;

private:


	void ResourceLoad();
	void CreateBackGround();
};

