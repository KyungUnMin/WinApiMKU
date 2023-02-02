#pragma once
#include "ComponentBase.h"
#include <vector>

enum class BubbleMissleType
{
	Normal,
	Fire,
	Water,
	Electronic,
	Rainbow,
	Windy,
	Melody
};

class PlayerBase;
class BubbleMissleBase;

class BubbleSpawner : public ComponentBase
{
public:
	static std::vector<BubbleMissleBase*>	Bubbles;
	static void AllDeath();


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
	PlayerBase*					Player		= nullptr;
	BubbleMissleType		Type		= BubbleMissleType::Normal;


	BubbleMissleBase* CreateBubble();
};

