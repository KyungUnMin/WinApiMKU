#pragma once
#include "MonsterMissleBase.h"

class MonsterMissle_WarurinBress : public MonsterMissleBase
{
public:
	static const std::string AniNames[2];
	static const float4 RenderScale;

	MonsterMissle_WarurinBress();
	~MonsterMissle_WarurinBress();

	MonsterMissle_WarurinBress(const MonsterMissle_WarurinBress& _Other) = delete;
	MonsterMissle_WarurinBress(MonsterMissle_WarurinBress&& _Other) noexcept = delete;
	MonsterMissle_WarurinBress& operator=(const MonsterMissle_WarurinBress& _Other) = delete;
	MonsterMissle_WarurinBress& operator=(const MonsterMissle_WarurinBress&& _Other) noexcept = delete;

	void SetDir(const float4& _Dir) override;
	void ThrowMissle(const float4& _Dir) override;

protected:
	void Start() override;
	void Update(float _DeltaTime)  override;

private:
	enum class WB_State
	{
		Ready,
		Throw,
	};

	float4								ScreenSize				= float4::Zero;
	const float						ScreenOutOffset	= 100.f;

	WB_State							CurState					= WB_State::Ready;
	const float						MoveSpeed				= 500.f;

	const std::string_view	LeftImagePath		= "Left_WarurinBress.bmp";
	const std::string_view	RightImagePath		= "Right_WarurinBress.bmp";

	void ResourceLoad();
};

