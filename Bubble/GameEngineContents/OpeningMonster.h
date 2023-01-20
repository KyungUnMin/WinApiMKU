#pragma once
#include <map>
#include <GameEngineCore/GameEngineActor.h>

class OpeningMonster : public GameEngineActor
{
public:
	OpeningMonster();
	~OpeningMonster();

	OpeningMonster(const OpeningMonster& _Other) = delete;
	OpeningMonster(OpeningMonster&& _Other) noexcept = delete;
	OpeningMonster& operator=(const OpeningMonster& _Other) = delete;
	OpeningMonster& operator=(const OpeningMonster&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	class MonInfo
	{
	public:
		std::string				AniName = "";
		int							AniIndexCount = 0;
		std::pair<int, int>		PosIndex;
		float						AniInterval = 1.f;
	};

	static const MonInfo								Info[38];
	float4														MonsterPos[4][11];
};

