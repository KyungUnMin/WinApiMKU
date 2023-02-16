#pragma once
#include "RoundLevelBase.h"

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
	void ChangeNextLevel() override;

private:


	void ResourceLoad();
	void CreateBackGround();
	void CreateBubbleDest();
	void CreateMonsters();
};

