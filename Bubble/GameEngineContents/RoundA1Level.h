#pragma once
#include <map>
#include <vector>
#include "RoundLevelBase.h"
#include "ContentsEnum.h"

class BackGround;
class BubbleSpawner;
class StageBubbleSpawnerInfo;


class RoundA1Level : public RoundLevelBase
{
public:
	RoundA1Level();
	~RoundA1Level();

	RoundA1Level(const RoundA1Level& _Other) = delete;
	RoundA1Level(RoundA1Level&& _Other) noexcept = delete;
	RoundA1Level& operator=(const RoundA1Level& _Other) = delete;
	RoundA1Level& operator=(const RoundA1Level&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;
	void ChangeNextLevel() override;

private:
	std::vector<std::vector<StageBubbleSpawnerInfo>> StageBubbleSpawnCtrl;

	void ResourceLoad();

	//2개의 배경 애니메이션 생성
	void CreateBackGround();

	void CreateBubbleDest();

	void CreateMonsters();

	void CreateStageBubbleSpawners();


	void Update_StageBubbleSpawner(float _DeltaTime);
};

