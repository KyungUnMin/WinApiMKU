#pragma once
#include "NatureMissleBase.h"

class NatureMissle_Electronic : public NatureMissleBase
{
public:
	static const std::string_view ImagePath;
	static const std::string_view MoveAniName;
	static const std::string_view AttachAniName;
	static const std::string_view DestroyAniName;

	NatureMissle_Electronic();
	~NatureMissle_Electronic() override;

	NatureMissle_Electronic(const NatureMissle_Electronic& _Other) = delete;
	NatureMissle_Electronic(NatureMissle_Electronic&& _Other) noexcept = delete;
	NatureMissle_Electronic& operator=(const NatureMissle_Electronic& _Other) = delete;
	NatureMissle_Electronic& operator=(const NatureMissle_Electronic&& _Other) noexcept = delete;

	void DestroyByBoss() override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	enum class State
	{
		Move,
		PlayerAttach,
		Destroy
	};

	bool					IsPlayerAttached	= false;
	State				NowState					= State::Move;
	float4				ScreenSize				= float4::Zero;
	const float		ScreenOutOffset	= 50.f;
	const float4	MoveSpeed				= float4{ 400.f, 0.f };

	void LoadSFX();
	void ResourceLoad();
	void CreateAnimation();

	void Update_Move(float _DeltaTime);
	void Update_Attach(float _DeltaTime);
	void MonsterKill();
};

