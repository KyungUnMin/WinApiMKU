#pragma once
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineActor.h>
#include "ComponentBase.h"
#include "ContentsEnum.h"


class PlayerBase;
class RoundLevelBase;

class BubbleSpawner : public GameEngineActor
{
public:
	static const float4 SpawnOffset;

	BubbleSpawner();
	~BubbleSpawner() override;

	BubbleSpawner(const BubbleSpawner& _Other) = delete;
	BubbleSpawner(BubbleSpawner&& _Other) noexcept = delete;
	BubbleSpawner& operator=(const BubbleSpawner& _Other) = delete;
	BubbleSpawner& operator=(const BubbleSpawner&& _Other) noexcept = delete;

	void CreateBubble(const float4 _Dir);

	/*inline PlayerBase* GetPlayer()
	{
		return Player;
	}

	inline void SetPlayer(PlayerBase* _Player)
	{
		Player = _Player;
	}*/

	inline void SetPlayer(PlayerBase* _Player)
	{
		Player = _Player;
	}

	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

protected:
	

private:
	RoundLevelBase*		RoundLevel		= nullptr;
	PlayerBase*					Player				= nullptr;
	BubbleMissleType		Type				= BubbleMissleType::Normal;

};

