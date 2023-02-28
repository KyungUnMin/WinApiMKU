#pragma once
#include <GameEngineCore/GameEngineActor.h>

class TextLine;

enum class NavigationType
{
	CourseSelect,
	WorldClear,
};

class NavigationUI : public GameEngineActor
{
public:
	static const std::string_view WorldImgPath;
	static const std::string_view CourseImgPath;
	static const std::string_view TextValue[2];

	NavigationUI();
	~NavigationUI() override;

	NavigationUI(const NavigationUI& _Other) = delete;
	NavigationUI(NavigationUI&& _Other) noexcept = delete;
	NavigationUI& operator=(const NavigationUI& _Other) = delete;
	NavigationUI& operator=(const NavigationUI&& _Other) noexcept = delete;

	void CreateImage(NavigationType _ImgType);
	void Clear();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	const float4	TextScale		= float4{ 20.f, 30.f };
	TextLine*			Texts[2]		= { nullptr, nullptr };

	void ResourceLoad();
	void CreateTexts();

};

