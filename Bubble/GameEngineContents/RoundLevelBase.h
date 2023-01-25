#pragma once
#include <string>
#include <string_view>
#include <GameEngineCore/GameEngineLevel.h>

class BackGround;

class RoundLevelBase : public GameEngineLevel
{
public:
	RoundLevelBase();
	~RoundLevelBase();

	RoundLevelBase(const RoundLevelBase& _Other) = delete;
	RoundLevelBase(RoundLevelBase&& _Other) noexcept = delete;
	RoundLevelBase& operator=(const RoundLevelBase& _Other) = delete;
	RoundLevelBase& operator=(const RoundLevelBase&& _Other) noexcept = delete;

	bool IsLastStage();

protected:
	void Loading() override{}
	void Update(float _DeltaTime) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override {}

	void LoadObstacle(const std::string_view& _RoundName, int _X, int _Y);

	template <typename RenderOrder>
	void CreateObstacle(const float4& _ArrangeDir, RenderOrder _Order)
	{
		CreateObstacle(_ArrangeDir, static_cast<int>(_Order));
	}

	void CreateObstacle(const float4& _ArrangeDir, int _Order);

	bool MoveToNextStage();

private:
	std::string		ImageName	= "Round";
	BackGround*	Obstacles	= nullptr;

	bool					IsMoving		= false;
	size_t				NowIndex	= 0;
	float4				MoveDir		= float4::Zero;
	const float		MoveSpeed	= 500.f;

	void ArrangeStage(float4 _Dir, size_t _CenterIndex);
};

