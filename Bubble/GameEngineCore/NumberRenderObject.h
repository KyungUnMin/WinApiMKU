#pragma once
#include <vector>

#include "GameEngineObject.h"
#include "GameEngineRender.h"

enum class Align
{
	Left,
	Right,
	Center
};

class GameEngineActor;
class NumberRenderObject : public GameEngineObject
{
public:
	NumberRenderObject();
	~NumberRenderObject();

	NumberRenderObject(const NumberRenderObject& _Other) = delete;
	NumberRenderObject(NumberRenderObject&& _Other) noexcept = delete;
	NumberRenderObject& operator=(const NumberRenderObject& _Other) = delete;
	NumberRenderObject& operator=(NumberRenderObject&& _Other) noexcept = delete;
	

	void SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order, int _TransColor, const std::string_view& _NegativeName = "");
	void SetValue(int _Value);

	void SetMove(float4 _RenderPos);
	void SetAlign(Align _Align);

	void SetCameraEffect(bool _EffectSetting)
	{
		CameraEffect = _EffectSetting;
	}

	inline void SetRenderPos(float4 _Pos)
	{
		Pos = _Pos;
	}

	inline int GetValue()
	{
		return Value;
	}

protected:

private:
	int							Order				= 0;
	float4						NumberScale	= {};
	float4						Pos					= {};
	int							Value				= 0;
	int							TransColor		= RGB(255, 0, 255);
	Align						AlignState		= Align::Left;
	bool							Negative			= false;
	bool							CameraEffect	= false;

	std::string_view		ImageName		= std::string_view();

	std::string_view		NegativeName	= std::string_view();

	std::vector<GameEngineRender*> NumberRenders = std::vector<GameEngineRender*>();
	GameEngineRender* NegativeRender = nullptr;
};

