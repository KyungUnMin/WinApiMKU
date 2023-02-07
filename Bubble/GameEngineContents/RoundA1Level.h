#pragma once
#include "RoundLevelBase.h"

class BackGround;

class RoundA1Level : public RoundLevelBase
{
public:
	static const std::vector<float4>								PlayerSpanwPos;
	static const std::vector<std::vector<float4>>		BubbleDestPos;

	RoundA1Level();
	~RoundA1Level();

	RoundA1Level(const RoundA1Level& _Other) = delete;
	RoundA1Level(RoundA1Level&& _Other) noexcept = delete;
	RoundA1Level& operator=(const RoundA1Level& _Other) = delete;
	RoundA1Level& operator=(const RoundA1Level&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;

private:
	void ResourceLoad();

	//2개의 배경 애니메이션 생성
	void CreateBackGround();

	void CreateBubbleDest();
};

