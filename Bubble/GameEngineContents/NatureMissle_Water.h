#pragma once
#include <GameEngineCore/GameEngineResources.h>
#include "NatureMissleBase.h"

class MonsterBase;

class NatureMissle_Water : public NatureMissleBase
{
public:
	static const std::string_view		ImagePath;
	static const float4						MoveColScale;

	static size_t AllCount;
	static GameEngineSoundPlayer WaterWave;

	NatureMissle_Water();
	~NatureMissle_Water() override;

	NatureMissle_Water(const NatureMissle_Water& _Other) = delete;
	NatureMissle_Water(NatureMissle_Water&& _Other) noexcept = delete;
	NatureMissle_Water& operator=(const NatureMissle_Water& _Other) = delete;
	NatureMissle_Water& operator=(const NatureMissle_Water&& _Other) noexcept = delete;

	inline void InitPos(const float4& _StartPos, const float4& _Dir)
	{
		StartPos = _StartPos;
		SetPos(_StartPos);

		StartDir = _Dir;
		SetDir(StartDir);
	}

	void SetCreateCount(int _Count, bool _IsFirst = true) 
	{
		WaterCount = _Count;
		IsFirst = _IsFirst;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime)  override;

private:
	const float						ScreenOutOffsetY	= 50.f;
	const float4					MoveSpeed				= { 500.f, 500.f };

	const float						CreateChildTime		= 0.03f;
	float4								StartPos					= float4::Zero;
	float4								StartDir					= float4::Zero;
	int									WaterCount				= 0;
	bool									IsFirst						= false;
	std::list<MonsterBase*>	DragMonsters;

	void LoadSFX();
	void ResourceLoad();
	void CreateChild();

	void SetImageFrame();
	void Move(float _DeltaTime);
	void MonsterKill();
	void MonsterDrag();
	void PlayerDrag();
};

