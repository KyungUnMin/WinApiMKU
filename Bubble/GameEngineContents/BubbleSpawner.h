#pragma once
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"


class PlayerBase;
class RoundLevelBase;

enum class BubbleColor
{
	Green,
	Blue,
	Yellow,
	Pink,
	UNKNOWN
};

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

	void CreateBubble();

	inline void SetPlayer(PlayerBase* _Player)
	{
		Player = _Player;
	}

	void Start() override;
	void Update(float _DeltaTime) override;

	inline void SetBubbleType(BubbleMissleType _Type)
	{
		Type = _Type;
	}

	inline void SetColor(BubbleColor _Color)
	{
		Color = _Color;
	}

protected:
	

private:
	RoundLevelBase*		RoundLevel		= nullptr;
	PlayerBase*					Player				= nullptr;
	BubbleMissleType		Type				= BubbleMissleType::Normal;
	BubbleColor				Color				= BubbleColor::UNKNOWN;
};

//--------------------------------------------------

class StageBubbleSpawnerInfo
{
public:
	StageBubbleSpawnerInfo()
	{
	}

	StageBubbleSpawnerInfo(BubbleSpawner* _StageSpawner, BubbleColor _Color = BubbleColor::UNKNOWN,float _LowTime = 0.5f, float _HighTime = 3.f)
		:StageSpawner(_StageSpawner)
		, LowTime(_LowTime)
		, HighTime(_HighTime)
	{
		StageSpawner->SetColor(_Color);
	}

	~StageBubbleSpawnerInfo()
	{

	}


	void BubbleCreate(float _DeltaTime)
	{
		NowTimer += _DeltaTime;
		if (NowTimer < DestTime)
			return;

		StageSpawner->CreateBubble();
		NowTimer -= DestTime;

		if (LowTime == HighTime)
		{
			DestTime = HighTime;
			return;
		}

		DestTime = LowTime + static_cast<float>(rand()) * (HighTime - LowTime) / RAND_MAX;
		return;
	}


private:
	BubbleSpawner*				StageSpawner		= nullptr;
	float								NowTimer			= 0.f;
	float								DestTime				= 0.f;
	const float						LowTime				= 0.5f;
	const float						HighTime				= 3.f;
};