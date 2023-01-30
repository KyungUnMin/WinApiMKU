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

	//이 레벨이 시작되었을때 이전 레벨에서 만들어준 Player의 위치를 설정
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:


	void ResourceLoad();
	void CreateBackGround();
};

