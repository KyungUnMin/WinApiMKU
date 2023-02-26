#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;

enum class BossPhase
{
	Normal,
	Upset,
	Rage,
};

class BossHpBar : public GameEngineActor
{
public:
	static BossHpBar* MainBossHP;
	static const std::string_view ImageName;

	BossHpBar();
	~BossHpBar();

	BossHpBar(const BossHpBar& _Other) = delete;
	BossHpBar(BossHpBar&& _Other) noexcept = delete;
	BossHpBar& operator=(const BossHpBar& _Other) = delete;
	BossHpBar& operator=(const BossHpBar&& _Other) noexcept = delete;

	bool ExcuteDamage(int _Damage);

	inline int GetHp()
	{
		return NowHP;
	}

	inline BossPhase GetPhase()
	{
		return Phase;
	}

	void Revive();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::vector<GameEngineRender*> HealthPoints;
	BossPhase	Phase		= BossPhase::Normal;
	int				NowHP		= 30;

	void ResourceLoad();
	void CreateHP();
};

