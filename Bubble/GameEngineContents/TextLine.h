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
	//TextLine::Texts.reserve
	static void Reserve(int _Capacity)
	{
		Texts.reserve(_Capacity);
	}

	//TextLine::Texts.clear
	static void Release()
	{
		Texts.clear();
	}

	//return TextLine::Texts[_Index]
	static TextLine* GetText(int _Index);

	TextLine();
	~TextLine() override;

	TextLine(const TextLine& _Other) = delete;
	TextLine(TextLine&& _Other) noexcept = delete;
	TextLine& operator=(const TextLine& _Other) = delete;
	TextLine& operator=(const TextLine&& _Other) noexcept = delete;

	//Text의 string 설정 및 색상 선택
	void SetString(const std::string_view& _String, TextLineColor _Color)
	{
		SetColor(_Color);
		StringValue = _String;
	}

	//Text의 string 설정 
	void SetString(const std::string_view& _String)
	{
		StringValue = _String;
	}

	//Text의 색상 선택
	void SetColor(TextLineColor _Color)
	{
		Color = _Color;
	}

	//글씨 크기 결정
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

