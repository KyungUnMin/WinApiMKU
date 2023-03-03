#pragma once
#include <vector>
#include "BubbleMissleStateBase.h"

class BubbleDestination;

class BubbleStateMove : public BubbleMissleStateBase
{
public:

	BubbleStateMove();
	~BubbleStateMove();

	BubbleStateMove(const BubbleStateMove& _Other) = delete;
	BubbleStateMove(BubbleStateMove&& _Other) noexcept = delete;
	BubbleStateMove& operator=(const BubbleStateMove& _Other) = delete;
	BubbleStateMove& operator=(const BubbleStateMove&& _Other) noexcept = delete;

	inline BubbleDestination* GetNowDest()
	{
		return NowDest;
	}

protected:
	void Init(PlayerCharacterType _CharType, BubbleMissleType _BubbleType) override;
	void Update(float _DeltaTime) override;

	void EnterState() override;

private:
	BubbleDestination*			NowDest			= nullptr;
	float4								ScreenSize		= float4::Zero;
	float								MoveSpeed		= 100.f;

	void ResourceLoad();
	void CreateAnimation(PlayerCharacterType _CharType, BubbleMissleType _BubbleType);

	//가장 가까운 BubbleDest의 위치로 목적지 설정
	void FindCloseDest();
	void MoveBubble(float _DeltaTime);
	void CycleScreenOut();
	void CheckDest();
};

