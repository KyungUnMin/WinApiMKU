#pragma once
#include <GameEngineCore/GameEngineActor.h>

class TextLine;

class BossDeadUI : public GameEngineActor
{
public:
	static const std::string_view ImagePath;
	static const std::string_view TextValue[2];

	BossDeadUI();
	~BossDeadUI() override;

	BossDeadUI(const BossDeadUI& _Other) = delete;
	BossDeadUI(BossDeadUI&& _Other) noexcept = delete;
	BossDeadUI& operator=(const BossDeadUI& _Other) = delete;
	BossDeadUI& operator=(const BossDeadUI&& _Other) noexcept = delete;

	void Clear();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	const float4	TextScale		= float4{ 20.f, 30.f };
	TextLine*			Texts[2]		= { nullptr, nullptr };

	void ResourceLoad();
	void CreateImage();
	void CreateTexts();

};

