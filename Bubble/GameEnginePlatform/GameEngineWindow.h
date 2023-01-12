#pragma once
#include <Windows.h>
#include <string>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineImage;

class GameEngineWindow
{
public:
	static void WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos);

	static void SettingWindowSize(float4 _Size);
	static void SettingWindowPos(float4 _Pos);

	static int	  WindowLoop(void(*_Start)(), void(*_Loop)(), void(*_End)());

	static HWND GetHWnd() 
	{
		return HWnd; 
	}

	static HDC GetWindowBackBufferHdc() 
	{ 
		return WindowBackBufferHdc; 
	}

	static GameEngineImage* GetDoubleBufferImage()
	{
		return DoubleBufferImage;
	}

	static float4 GetScreenSize()
	{
		return ScreenSize;
	}

	static void DoubleBufferClear();
	static void DoubleBufferRender();

	GameEngineWindow();
	~GameEngineWindow();

	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;

protected:

private:
	static HWND						HWnd;
	static HDC							WindowBackBufferHdc;
	static GameEngineImage*	BackBufferImage;
	static GameEngineImage*	DoubleBufferImage;

	static float4						WindowSize;
	static float4						ScreenSize;
	static float4						WindowPos;
};

