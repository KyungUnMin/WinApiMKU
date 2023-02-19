#pragma once
#include "MonsterMissleBase.h"

class RoundLevelBase;

class MonsterMissle_HidegonsBress : public MonsterMissleBase
{
public:
	static const std::string AniNames[2];
	static const float4 RenderScale;

	MonsterMissle_HidegonsBress();
	~MonsterMissle_HidegonsBress();

	MonsterMissle_HidegonsBress(const MonsterMissle_HidegonsBress& _Other) = delete;
	MonsterMissle_HidegonsBress(MonsterMissle_HidegonsBress&& _Other) noexcept = delete;
	MonsterMissle_HidegonsBress& operator=(const MonsterMissle_HidegonsBress& _Other) = delete;
	MonsterMissle_HidegonsBress& operator=(const MonsterMissle_HidegonsBress&& _Other) noexcept = delete;

	void ThrowMissle(const float4& _Dir) override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	enum class HB_State
	{
		Throw,
		Attach,
	};

	HB_State							CurState				= HB_State::Throw;
	const float						MoveSpeed			= 500.f;
	RoundLevelBase*			RoundLevel			= nullptr;

	const std::string_view	LeftImagePath	= "Left_HidegonsBress.bmp";
	const std::string_view	RightImagePath	= "Right_HidegonsBress.bmp";

	void ResourceLoad();
	void CreateAnimation();
	void ChangeNowStateAni();
};

