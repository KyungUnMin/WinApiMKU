#pragma once
#include "RoundLevelBase.h"

class BackGround;

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

	//이 레벨이 시작되었을때 이전 레벨에서 만들어준 Player의 위치를 설정
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	void ResourceLoad();

	//2개의 배경 애니메이션 생성
	void CreateBackGround();
};

