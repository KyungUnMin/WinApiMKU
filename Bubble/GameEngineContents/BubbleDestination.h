#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineCollision;
class RoundLevelBase;

class BubbleDestination : public GameEngineActor
{
public:
	static const float4 CollisionScale;

	BubbleDestination();
	~BubbleDestination() override;

	BubbleDestination(const BubbleDestination& _Other) = delete;
	BubbleDestination(BubbleDestination&& _Other) noexcept = delete;
	BubbleDestination& operator=(const BubbleDestination& _Other) = delete;
	BubbleDestination& operator=(const BubbleDestination&& _Other) noexcept = delete;

	inline void SetStageIndex(size_t _StageIndex)
	{
		StageIndex = _StageIndex;
	}

	inline size_t GetStageIndex()
	{
		return StageIndex;
	}

	void SetNextDest(BubbleDestination* _Next);

	inline BubbleDestination* GetNextDest()
	{
		return NextDest;
	}

protected:
	void Start() override;
	void Render(float _DeltaTime) override;

private:
	size_t								StageIndex		= 0;
	GameEngineCollision*		CollisionPtr		= nullptr;
	BubbleDestination*			NextDest			= nullptr;
	RoundLevelBase*			RoundLevel		= nullptr;

	HPEN								PathLinePen;
};

