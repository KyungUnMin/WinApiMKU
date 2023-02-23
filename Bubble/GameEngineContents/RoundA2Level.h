#pragma once
#include "RoundLevelBase.h"

class StageBubbleSpawnerInfo;

class RoundA2Level : public RoundLevelBase
{
public:
	RoundA2Level();
	~RoundA2Level();

	RoundA2Level(const RoundA2Level& _Other) = delete;
	RoundA2Level(RoundA2Level&& _Other) noexcept = delete;
	RoundA2Level& operator=(const RoundA2Level& _Other) = delete;
	RoundA2Level& operator=(const RoundA2Level&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;
	void ChangeLastLevel() override;
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

