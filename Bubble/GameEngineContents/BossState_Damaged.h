#pragma once
#include <string_view>
#include "BossStateBase.h"

class GameEngineRender;

class BossState_Damaged : public BossStateBase
{
public:
	static const std::string_view SteamImagePath;
	static const std::string_view SteamAniName;
	static const float4 SteamRenderScale;

	BossState_Damaged();
	~BossState_Damaged() override;

	BossState_Damaged(const BossState_Damaged& _Other) = delete;
	BossState_Damaged(BossState_Damaged&& _Other) noexcept = delete;
	BossState_Damaged& operator=(const BossState_Damaged& _Other) = delete;
	BossState_Damaged& operator=(const BossState_Damaged&& _Other) noexcept = delete;
	
protected:
	void Start() override;
	void EnterState() override;
	void Update(float _DeltaTime) override;

private:
	const size_t		SteamCnt			= 4;
	const float4	StartOffset		= float4{ 0.f, -100.f };
	

	std::vector<std::pair<GameEngineRender*, float>> AngrySteams;
	void StreamResourceLoad();
	void CreateStreamAni();
};

