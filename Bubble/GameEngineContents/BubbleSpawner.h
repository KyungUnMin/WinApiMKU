#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "ComponentBase.h"
#include "ContentsEnum.h"


class PlayerBase;
class RoundLevelBase;

class BubbleSpawner : public ComponentBase
{
public:
	static const float4 SpawnOffset;

	BubbleSpawner();
	~BubbleSpawner();

	BubbleSpawner(const BubbleSpawner& _Other) = delete;
	BubbleSpawner(BubbleSpawner&& _Other) noexcept = delete;
	BubbleSpawner& operator=(const BubbleSpawner& _Other) = delete;
	BubbleSpawner& operator=(const BubbleSpawner&& _Other) noexcept = delete;

	inline PlayerBase* GetPlayer()
	{
		return Player;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	RoundLevelBase*		RoundLevel		= nullptr;
	PlayerBase*					Player				= nullptr;
	BubbleMissleType		Type				= BubbleMissleType::Normal;

	void CreateBubble();
};

