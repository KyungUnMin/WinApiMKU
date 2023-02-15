#pragma once
#include <map>
#include "RoundLevelBase.h"
#include "ContentsEnum.h"

class BackGround;
class MonsterSpawnerBase;

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

private:
	std::map<MonsterType, MonsterSpawnerBase*> MonSpanwers;

	void ResourceLoad();

	//2개의 배경 애니메이션 생성
	void CreateBackGround();

	void CreateBubbleDest();

	void CreateMonster();
};

