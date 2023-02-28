#pragma once
#include "RoundLevelBase.h"

class StageBubbleSpawnerInfo;

class RoundA3Level : public RoundLevelBase
{
public:
	RoundA3Level();
	~RoundA3Level();

	RoundA3Level(const RoundA3Level& _Other) = delete;
	RoundA3Level(RoundA3Level&& _Other) noexcept = delete;
	RoundA3Level& operator=(const RoundA3Level& _Other) = delete;
	RoundA3Level& operator=(const RoundA3Level&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;
	void StartLastStage() override;

private:
	std::vector<std::vector<StageBubbleSpawnerInfo>> StageBubbleSpawnCtrl;

	void ResourceLoad();
	void CreateBackGround();
	void CreateBubbleDest();
	void CreateMonsters();

	void CreateStageBubbleSpawners();
	void Update_StageBubbleSpawner(float _DeltaTime);
};

