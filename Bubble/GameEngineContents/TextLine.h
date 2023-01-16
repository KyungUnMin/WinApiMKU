#pragma once
#include <string>
#include <vector>
#include <string_view>
#include <GameEngineCore/GameEngineActor.h>

enum class TextLineColor
{
	White			= 63 * 0,
	LightGreen	= 63 * 1,
	Pink				= 63 * 2,
	Sky				= 63 * 3,
	Yellow			= 63 * 4,
	Green			= 63 * 5,
	Blue				= 63 * 6,
	Pupple			= 63 * 7,
	Red				= 63 * 8,
	Gold				= 63 * 9
};

class GameEngineImage;

class TextLine : public GameEngineActor
{
public:
	static void Reserve(int _Capacity)
	{
		Texts.reserve(_Capacity);
	}

	static void Release()
	{
		Texts.clear();
	}

	static TextLine* GetText(int _Index);

	TextLine();
	~TextLine() override;

	TextLine(const TextLine& _Other) = delete;
	TextLine(TextLine&& _Other) noexcept = delete;
	TextLine& operator=(const TextLine& _Other) = delete;
	TextLine& operator=(const TextLine&& _Other) noexcept = delete;

	void SetString(const std::string_view& _String, TextLineColor _Color)
	{
		SetColor(_Color);
		StringValue = _String;
	}

	void SetString(const std::string_view& _String)
	{
		StringValue = _String;
	}

	void SetColor(TextLineColor _Color)
	{
		Color = _Color;
	}

	void SetScale(const float4& _Scale)
	{
		Scale = _Scale;
	}

protected:
	void Start() override;
	void Render(float _DeltaTime) override;

private:
	static std::vector<TextLine*> Texts;

	std::string					StringValue	= std::string();
	TextLineColor				Color			= TextLineColor::White;

	GameEngineImage*		Image			= nullptr;
	float4							Scale			= float4::Zero;
};

