#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;

class BossDeadBox : public GameEngineActor
{
public:
	static const std::string_view ImagePath;

	BossDeadBox();
	~BossDeadBox() override;

	BossDeadBox(const BossDeadBox& _Other) = delete;
	BossDeadBox(BossDeadBox&& _Other) noexcept = delete;
	BossDeadBox& operator=(const BossDeadBox& _Other) = delete;
	BossDeadBox& operator=(const BossDeadBox&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override
	{
		CreatedItemCnt = 0;
	}

private:
	enum class State
	{
		Close,
		Open,
	};

	State							NowState				= State::Close;
	GameEngineRender*	RenderPtr			= nullptr;
	const float4				ItemOffset			= { 0.f, -100.f };
	size_t							CreatedItemCnt	= 0;

	void ResourceLoad();
	void Update_Close();
	void Update_Open(float _DeltaTime);
};

